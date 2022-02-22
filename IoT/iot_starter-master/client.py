import asyncio
import websockets
import json
runcount = 0

async def send_message(websocket, message, client_id):
    outward_message = {
        'client_id': client_id,
        'payload': message
    }
    await websocket.send(json.dumps(outward_message))

async def recv_message(websocket):
    message = json.loads(await websocket.recv())
    return message['payload']

async def main():
    uri = "ws://localhost:6789"
    async with websockets.connect(uri) as websocket:
        # After joining server will send client unique id.
        message = input("What is your message?\nType 'end' to exit.\n")
        if message == "end":
            return 1
        clientid = json.loads(await websocket.recv())
        print(message)
        # Get the client_id from the join message
        if clientid['type'] == 'join_evt':
            client_id = clientid['client_id']
        else:
            # If first message is not the join message exit
            print("Did not receive a correct join message")
            return 0
        # Send a ping to the server
        await send_message(websocket, 'ping', client_id)
        # Wait for the 'ping' response from the server
        response = await recv_message(websocket)
        print("The Server Sent Back:")
        print(response)
        return 0

while __name__ == "__main__":
    print("Echo client-----------", runcount)
    runcount+=1
    if asyncio.run(main()):
        break  