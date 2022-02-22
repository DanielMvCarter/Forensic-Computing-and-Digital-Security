import asyncio
import websockets
import json
runcount = 0
from ham import *

async def send_message(websocket, message, client_id):
    outward_message = {
        'client_id': client_id,
        'payload': message,
        'type': 'morse_evt'
    }
    await websocket.send(json.dumps(outward_message))

async def recv_message(websocket):
    message = json.loads(await websocket.recv())
    return message['payload']

async def main(message):
    uri = "ws://localhost:10102"
    async with websockets.connect(uri) as websocket:
        # After joining server will send client unique id.
        if message == "end":
            return 1
        clientid = json.loads(await websocket.recv())
        # print(message)
        # Get the client_id from the join message
        if clientid['type'] == 'join_evt':
            client_id = clientid['client_id']
        else:
            # If first message is not the join message exit
            print("Did not receive a correct join message")
            return 0
        # Send a message to the server
        await send_message(websocket, message, client_id)
        # Wait for the message response from the server
        response = await recv_message(websocket)
        print("Server response =", response)
        return response

################################################
# Function Name :send_echo
# Returns    : decoded
# Args       : sender, message
#
# Created by    : Daniel Carter
# Date created  : 25/03/21
# Description   : This function takes the user input sender and message, then passes it to ham_encode along with the receiver of echo
# this returns to the message variable which is then passed into main which sends the message and returns a response.
# the response then is decoded via ham_decode and is then printed out
################################################
def send_echo(sender, message):
    print("Sending Echo Message")
    message = ham_encode(sender,"echo", message)
    #Decode the response returned from main
    decoded = ham_decode(asyncio.run(main(message)))
    #Format and print the output
    print("Sender:",decoded[1], "\nReceiver:", decoded[0], "\nMessage:", decoded[2])
    return decoded

################################################
# Function Name :send_time
# Returns    : decoded
# Args       : sender
#
# Created by    : Daniel Carter
# Date created  : 25/03/21
# Description   : This function takes the user input sender then passes it to ham_encode along with the receiver of time
# this returns to the message variable which is then passed into main which sends the message and returns a response.
# the response then is decoded via ham_decode and is then printed out
################################################
def send_time(sender):
    print("Sending Time Message")
    message = ham_encode( sender, "time","hello world")
    #Decode the response returned from main
    decoded = ham_decode(asyncio.run(main(message)))
    #Format and print the output
    print("Sender:",decoded[1],"\nReceiver:", decoded[0], "\nTime:", decoded[2])
    return decoded

while __name__ == "__main__":
    sender = input("Sender: ")
    message = input ("Message: ")
    send_echo(sender, message)
    send_time(sender)