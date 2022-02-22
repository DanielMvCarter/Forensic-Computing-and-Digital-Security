import asyncio
import websockets
import base64
from struct import *
import time

################################################
# Function Name :compute_checksum
# Returns    : checksum
# Args       : so_port,de_port,payload
#
# Created by    : Daniel Carter
# Date created  : 15/04/21
# Description   : Take in the seperated packet bytes then remake the packet with a zero byte checksum,
# ensure that the packet is even, then get the 1's compliment of checksum. Finally evaluate if checksum matches 
# the initial value from the packet, return accordingly.
################################################

def compute_checksum(so_port,de_port,payload): 
    #Create intial check sum, then create a zero byte checksum
    checksum = bytes(0)
    length =8 + len(payload)
    length = length.to_bytes(2, byteorder="little")

    #Recreate the packet concatenating all parts
    packet = so_port + de_port + length + checksum + payload
    #If there is an odd number of bytes add extra 0 byte to end
    if (len(packet) %2):
        packet += pack('!B', 0)
    checksum = 0
    # Bit shift for 1's compliment
    for i in range(0, len(packet), 2): 
        w = (packet[i] << 8) + (packet[i + 1])
        checksum += w
    checksum = (checksum >> 16) + (checksum & 0xFFFF)
    checksum = ~checksum & 0xFFFF
    return checksum

################################################
# Function Name :send_packet
# Returns    : N/A
# Args       : websocket, so_port, de_port, payload
#
# Created by    : Daniel Carter
# Date created  : 19/04/21
# Description   : Sends a packet to the server using the given header and payload data.
################################################

async def send_packet(websocket, so_port, de_port, payload):
    #Convert data into bytes.
    so_port= so_port.to_bytes(2, "little")
    de_port = de_port.to_bytes(2, "little")
    length = 8 + len(payload)
    length = length.to_bytes(2, "little")
    checksum = compute_checksum(so_port, de_port, payload).to_bytes(2, "little")
    #Create packet
    packet = so_port + de_port + length + checksum + payload
    #Encode packet 
    packet = base64.b64encode(packet)

    #Send the packet.
    await websocket.send(packet)
################################################
# Function Name :receive_and_decode_reply
# Returns    : N/A
# Args       : websocket
#
# Created by    : Daniel Carter
# Date created  : 14/04/21
# Description   : This function is called, then a message is received from the server, this is b64 encoded,
# this firstly needs to be decoded, then split up into each header and payload. These are then printed out as ints.
################################################

async def receive_and_decode_reply(websocket):
    #Get reply with b64 encoding from UDP server
    reply = await websocket.recv()
    print("Base64: ",reply)
    #Decode b64
    dec_reply = base64.b64decode(reply)
    print("Server Sent: ", dec_reply)
    #Get headers and payload from dec_reply
    so_port = dec_reply[0:2]
    de_port = dec_reply[2:4]
    length = dec_reply[4:6]
    checksum = dec_reply[6:8]
    payload = dec_reply[8:(int.from_bytes(length, 'little')+8)]

    Calc_checksum = compute_checksum(so_port, de_port, payload)
    #Check to see if calculated checksum is equal to the initial value
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

################################################
# Function Name : main
# Returns    : N/A
# Args       : N/A
#
# Created by    : Daniel Carter
# Date created  : 14/04/21
# Description   : This function creates the connection to the UDP server then calls the functions 
# to receive and decode a message. Compute the checksum of the decoded message and .......................................
################################################
async def main():
    uri = "ws://localhost:5612"
    async with websockets.connect(uri) as websocket:

        await receive_and_decode_reply(websocket)

        while True:
            
            await send_packet(websocket, 0, 542, b"1111")
            await receive_and_decode_reply(websocket)

            time.sleep(1)
        
while __name__ == "__main__":
    if asyncio.run(main()):
        break 