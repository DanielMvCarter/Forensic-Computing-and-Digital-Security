Worksheet 3 README
==================
The task of this worksheet was to create a program which would firstly be able to receive a packet from a UDP server, then print out the information in plain text. Secondly, the checksum needed to be calculated, this will be used in the first instance to check that the checksum received from the server matches that of the packet to ensure that there has been no data loss. This will then also provide functionality for task 3, which is to send a packet back to the server and await a new response.

How to run
-----------------
As there is no user input required for this program, it will automatically connect, await a response from the UDP server, decode and seperate out the packet then print it, all by simply running the program.

Part 1 Basic Client
-------------------
Similarly to previous tasks this requires a connection to the remote development machine, using port '5612' will connect to a UDP server, this connection is then passed to the receive_and_decode_reply function.
```python
async def main():
    uri = "ws://localhost:5612"
    async with websockets.connect(uri) as websocket:

        await receive_and_decode_reply(websocket)
```
Server response:
```
b'CgAqACEAyztXZWxjb21lIHRvIElvVCBVRFAgU2VydmVy'
```

Firstly the response is captured from the server,UDP packets are encoded with Base 64, thus it is to be decoded. 

```python
async def receive_and_decode_reply(websocket):
    reply = await websocket.recv() 
    print("Base64: ",reply)
    dec_reply = base64.b64decode(reply)
    print("Server Sent: ", dec_reply)
```
This yields the result:
```
b'\n\x00*\x00!\x00\xcb;Welcome to IoT UDP Server'
```
Now that the data is in plain text, the bytes can be seen and the headers and payload need seperating. Using the python slice[start:stop] notation, the individual headers can be accessed:

Source port: bytes 0 and 1.
Destination Port: bytes 2 and 3.
Length of the packet: bytes 4 and 5.
Checksum: bytes 6 and 7.

```python
so_port = dec_reply[0:2]
de_port = dec_reply[2:4]
length = dec_reply[4:6]
checksum = dec_reply[6:8]
payload = dec_reply[8:(int.from_bytes(length, 'little')+8)]
```
Once the bytes have been accessed they are converted into an integer for printing, little endian needs to be specified for successful conversion.

```python
print("Source Port: ", int.from_bytes(so_port, 'little'),
        "\n""Dest Port: ", int.from_bytes(de_port, 'little'),
        "\nData Length: ",  int.from_bytes(length, 'little'),
        "\nChecksum: ",  int.from_bytes(checksum, 'little'),
        "\n==============================================================")
```
Lastly, the payload needs to be decoded as it may be any form of binary data depending on which application has sent it. In this case it is a string encoded through UTF-8. Using the slice notation again, the start of the payload is accessed along with the total length of the packet+8, this is then decoded.

```python
"\nPayload: ", dec[8:(length+8)].decode("utf-8"))
```

This creates the following output:

```bash
Base64:  b'CgAqACEAyztXZWxjb21lIHRvIElvVCBVRFAgU2VydmVy'
Server Sent:  b'\n\x00*\x00!\x00\xcb;Welcome to IoT UDP Server'
Source Port:  10 
Dest Port:  42 
Data Length:  33 
Checksum:  15307 
Payload:  Welcome to IoT UDP Server 
```

Part 2 Compute Checksum
-----------------------
A checksum is an integer which is created based upon the information within the packet, this can then be used against the packet to ensure that it has been received correctly. This function is first called from within 'receive_and_decode_reply', the source port, destination port and payload from the reply are passed in to it, with the return being stored in a variable for later checking.

```python
 Calc_checksum = compute_checksum(so_port, de_port, payload)
```
To begin with the final two headers must be created, firstly, a zero byte checksum is made, then the length of the packet is calculated, 8 bytes for the headers + the length of the payload. These are both store as bytes.

```python
def compute_checksum(so_port,de_port,payload): 
    checksum = bytes(0)
    length =8 + len(payload)
    length = length.to_bytes(2, byteorder="little")
```

The packet is then stitched back together with the new checksum, following on from this we check whether the packet is an even length or odd. In the case that it is odd we must add an extra 0 byte to end.

```python
packet = so_port + de_port + length + checksum + payload
    if (len(packet) %2):
        packet += pack('!B', 0)
    checksum = 0  
```

Finally in order to calculate the checksum, the 1's compliment is made by a leftward bitshift of 8, this turns each header into an 8 bit value.

```python
for i in range(0, len(packet), 2): 
        w = (packet[i] << 8) + (packet[i + 1])
        checksum += w
```
Next, a rightward bitshift of 16 bits along with a check AND 11111111 is done, this can then be used finally to perform a bitwise NOT to find the final calculated checksum.
```python
    checksum = (checksum >> 16) + (checksum & 0xFFFF)
    checksum = ~checksum & 0xFFFF
    return checksum
```

Control is then passed back to the calling function, here a check is performed upon the calculated checksum, if it matches that of the checksum from the packet's header, then the data is valid and therefore can be printed as well as returned. However, if it does not match then a value error is raised.

```python
if Calc_checksum==int.from_bytes(checksum,'little'):
    #Print everything as an int rather than byte
        print("Source Port: ", int.from_bytes(so_port, 'little'),
        "\n""Dest Port: ", int.from_bytes(de_port, 'little'),
        "\nData Length: ",  int.from_bytes(length, 'little'),
        "\nChecksum: ",  int.from_bytes(checksum, 'little'),
        "\nPayload: ", payload.decode("utf-8"),
        "\nCalculated Checksum:" ,Calc_checksum,
        "\n==============================================================")
        return int.from_bytes(so_port, 'little'), int.from_bytes(de_port, 'little'), int.from_bytes(length, 'little'), int.from_bytes(checksum, 'little'),payload.decode("utf-8")
    else:
        raise ValueError ("Checksum does not match")
```

Part 3 Send a UDP Packet
------------------------
To begin with, the main function was expanded into a while loop, this would then call the new 'send_packet' function then use the 'receive_and_decode_reply' to interpret the new response.

```python
        while True:
            
            await send_packet(websocket, 0, 542, b"1111")
            await receive_and_decode_reply(websocket)

            time.sleep(1)
```
The first task is to create all of the apropriate headers, the souruce, destination and payload are passed in, these are converted into bytes, the length is then calculated and finally the checksum is calculated through the use of the task 2 'compute_checksum' function.

```python
async def send_packet(websocket, so_port, de_port, payload):
    so_port= so_port.to_bytes(2, "little")
    de_port = de_port.to_bytes(2, "little")
    length = 8 + len(payload)
    length = length.to_bytes(2, "little")
    checksum = compute_checksum(so_port, de_port, payload).to_bytes(2, "little")
```
The packet must then be put together in the correct order of headers, then encoded into base 64, this encoded is then sent to the server.

```python
    packet = so_port + de_port + length + checksum + payload
    packet = base64.b64encode(packet)
    await websocket.send(packet)
```
This will then communicate back and forth with the UDP server getting the time, an example of the output is as follows:

```bash
==============================================================
Base64:  b'HgIAABAAKv4xMToyMzo1NQ=='
Server Sent:  b'\x1e\x02\x00\x00\x10\x00*\xfe11:23:55'
Source Port:  542 
Dest Port:  0 
Data Length:  16 
Checksum:  65066 
Payload:  11:23:55 
Calculated Checksum: 65066 
==============================================================
Base64:  b'HgIAABAAKf4xMToyMzo1Ng=='
Server Sent:  b'\x1e\x02\x00\x00\x10\x00)\xfe11:23:56'
Source Port:  542 
Dest Port:  0 
Data Length:  16 
Checksum:  65065 
Payload:  11:23:56 
Calculated Checksum: 65065 
==============================================================
```

Unit Tests
----------
Unit tests become considerably harder in regards to programs that run synchronously, for this reason I will only be testing the functions that are not running in this manner.

The only non-sync'ed function is checksum, this takes in values as bytes and returns an int checksum.
```python
 def test_checksum(self):
    so_port= 0 
    de_port = 542 
    self.assertEqual(UDP.compute_checksum(so_port.to_bytes(2, "little"),de_port.to_bytes(2, "little"), b"1111"),(29595))
def test_checksum_fail(self):
    so_port= 0 
    de_port = 542 
    self.assertNotEqual(UDP.compute_checksum(so_port.to_bytes(2, "little"),de_port.to_bytes(2, "little"), b"1111"),(1))
def test_checksum2(self):
    so_port= 10
    de_port = 42 
    self.assertEqual(UDP.compute_checksum(so_port.to_bytes(2, "little"),de_port.to_bytes(2, "little"), b"Welcome to IoT UDP Server"),(15307))
```
The results for these tests are that they all pass.
```bash
----------------------------------------------------------------------
Ran 3 tests in 0.000s

OK
```