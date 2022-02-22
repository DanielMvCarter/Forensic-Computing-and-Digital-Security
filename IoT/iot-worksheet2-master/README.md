Worksheet 2 - Part 1 Readme
============================

The assigment set was to create an encode and decode function for morse code through the use of a binary tree. This was completed through three files, tree.py, morse.py and morseunit.py

The user interacts with the morse.py file calling either the encode or decode functions, these will then use functions within tree.py to populate the trees and return specific characters based upon the user's input. To make use of the encode function a user will need to call 'encode' along with a string in ascii, this function will then convert it to morse, print out the morse string and also return it to the user. The reverse will be done for 'decode where a morse string is given and an ascii string returned. All other functionality of the program is automated and does not require any user activity.

The implementation for the binary tree is within tree.py, this contains a class of binary_tree which is built with a rootID and two child nodes. These nodes will contain a tuple of both morse and ascii so that once the correct node has been found, the character can be converted.
```python
class binary_tree():
    def __init__(self, rootID):
        self.left = None
        self.right = None
        self.rootID = rootID
```

Populating the Trees
--------------------
Within the class there are functions which can be applied to a tree. The 'populate_ascii' function takes the set of tuples in "letter_morse" and enters them into a tree, this is done by evaluating where a note should be placed depending on the value of the ascii. 
 ```python
def populate_ascii(self, letter, morse):
    if self == None:
        return binary_tree((letter,morse))
    else:
        if letter < self.rootID[0]:
            self.left =binary_tree.populate_ascii(self.left,letter,morse)
            return self
        elif letter > self.rootID[0]:
            self.right = binary_tree.populate_ascii(self.right,letter,morse)
            return self
```
This final instance is in the case that the letter already exists in the tree, if it does then simply overwrite it.
```python
        else:
            self.rootID= (letter, morse)
            return self
```
A 'populate_morse' function is used to create the morse tree, it follows the order of the tuples within 'letter_morse' and inserts them top to bottom left to right. This is done by checking whether the current node's children are empty, if the left is then populate it, if not then try populate the right.
 ```python
def populate_morse(self):
    current = self
    newRow= []
    for char in letter_morse:
        if current.left == None:
            current.left = binary_tree(char)
        else:
            if current.right == None:
                current.right = binary_tree(char)
```
Otherwise a new row should be started and the left most node should be populated.
```python
            else:
                newRow.append(current.left)
                newRow.append(current.right)
                current = newRow.pop(0)
                current.left = binary_tree(char)
    return self
```
There are also functions which search the trees, a 'get_ascii' search which identifies if the character is a "." or "-", based upon this it will move left or right through the tree respectively. Once the end of the string has been reached then whichever node we have landed on must be the morse letter, then checking the tuple for the ascii character this can be added to the final string which will be returned.

Translating characters
----------------------
 ```python
def get_ascii(self, string):
    current = self
    final = ""
    current = self
    for char in string:
        if char == ".":
            current = current.left
        elif char == "-":
            current = current.right
```
There is error handling for an invalid string, any character outside of either a "." or "-" is not syntactically correct in morse. Alternatively if an empty node has been found then this should not be added to the string.
```python
        else:
            raise ValueError("Invalid String")
    if current.rootID[0] == "Empty":
            raise ValueError ("Empty node found")
    else:
        final += current.rootID[0]
    return final
```
 
A 'get_morse' search which follows the same logic as the 'populate_ascii' function, where it evaulates the character against the current root node and then decides which way to move through the tree. Similarly to the 'get_ascii' function this will then search the node it has landed in for the morse side of the tuple and return this value
```python
def get_morse(self, char):
    morse_output=""
    if self == None:
        raise ValueError ("No letter")
    else:
        if char < self.rootID[0]:
            return  binary_tree.get_morse(self.left,char)
        elif char > self.rootID[0]:
            return binary_tree.get_morse(self.right,char)
        else:
            morse_output = self.rootID[1]
    return morse_output
```

Printing Trees
--------------
The 'print_tree' function displays these two trees and how they are built differently. This allows us to see if the tree has been built as expected, the depth argument is used to format the output so that it can more easily be seen which level a node is on.
 ```python
def print_tree(tree, depth):
    if tree != None:
        for i in range(depth):
            print(' ', end ='')
        print(tree.rootID)
        binary_tree.print_tree(tree.left, depth+1)
        binary_tree.print_tree(tree.right, depth+1)
```
Calling the 'print_tree' function with the two types of populated tree give these outputs:
Morse Tree
```
 ('E', '.')
  ('I', '..')
   ('S', '...')
    ('H', '....')
     ('5', '.....')
      ('Empty', '......')
      ('Empty', '.....-')
     ('4', '....-')
      ('Empty', '....-.')
      ('Empty', '....--')
    ('V', '...-')
     ('Empty', '...-.')
      ('Empty', '...-..')
      ('Empty', '...-.-')
     ('3', '...--')
```
ASCII Tree
```
('A', '.-')
 ('5', '.....')
  ('4', '....-')
   ('3', '...--')
    ('2', '..---')
     ('&', '.-...')
      ('"', '.-..-.')
       ('!', '-.-.--')
      ('+', '.-.-.')
       ('*', '.--..')
        ('(', '-.--.')
```

Translating words
-----------------
Within Morse.py are functions that interface further with the tree, both the encode and decode functions reside here and to begin with they both create and populate a tree, they then work through the given string, they both create "words" out of the string, whether this is in ascii or morse, and pass these words letter by letter to the search functions in tree.py. The encode and decode functions handle spaces between words and character breaks for morse allowing for the output to be as clear as possible.

The firt part of the encode function creates and populates the ASCII binary tree, this loops through the tuples in letter_morse and passes them to the 'populate_ascii' function in tree.py
```python
def encode(string):
    ascii_root = binary_tree('ASCII')
    for char in letter_morse:
        ascii_tree =binary_tree.populate_ascii(ascii_root, char[0],char[1])
```
The user input needs to be consistent with the tree format so the upper function is called so that all characters are the same case. Then it searches through the string to create a word, this is based upon spaces, if a space is found then it is added to the output string, otherwise it must be part of the same word so translate it and then add it to the output string.
```python
    string = string.upper()
    e=""
    for char in string: 
        if char == " ":
            e += " "
        else:
            e += binary_tree.get_morse(ascii_tree,char)+ "|"
    print("Encoded string:",e)
    return e    
```
As in 'encode', 'decode' starts by building and populating the morse tree. 
```python
def decode(string):
    morse_root = binary_tree('MORSE')
    morse_tree = binary_tree.populate_morse(morse_root)
```
Then the input string is checked to see if it ends with a "|" this identifies the end of a morse character, it adds one if it does not exist. 
```python
    deliminated=""
    d=""
    if (string[len(string)-1]) != "|":
        string +="|"
```
Again in a similar fashion this function will then break the string down into words, if a space is found then add it to the output string, otherwise build up the morse letter, finally if a "|" is found then the end of the morse letter has been found and therefore it should be translated and added to the output string.
```python
    for char in string:
        if char == " ":
            d+= " "
        elif char != "|":
            deliminated += char
            if len(deliminated)>6:
                raise ValueError ("String too long")
        else:
            d += binary_tree.get_ascii(morse_tree,deliminated)
            deliminated = ""
    print("Decoded string:",d)
    return d
```

Part 1- Unit Testing
--------------------
In morseunit.py are the unit tests which have been created to test the functionality of the encode, decode and tree functions. These tests assert that the encode and decode functions return the expected outcome but also handle invalid arguments correctly. The tree tests check that the trees are built and populate correctly, and that the search functions return successfully.

These encode tests check that the strings are converted correctly from ascii to morse, regardless of case, they check that multiple words succeed and also that if an error is found that the program exits safely through error handling as opposed to crashing. With the extension of the trees in a later task there was also testing for the new characters.
```python
def test_encode_us(self):
    self.assertEqual(morse.encode('us'), '..-|...|') #Pass - Correct encoding
def test_encode_et(self):
    self.assertEqual(morse.encode('et'), '.|-|') #Pass - Correct encoding
def test_encode_sentence(self):
    self.assertEqual(morse.encode('test sentence'), '-|.|...|-| ...|.|-.|-|.|-.|-.-.|.|') #Pass - Correct encoding
def test_encode_fail_us(self):
    self.assertEqual(morse.encode('us'), '..-|') #Fail - Not given appropriate morse to match
def test_encode_exception(self):
    with self.assertRaises(ValueError): #Pass - None tree is given therefore when looking in self value error is raised
        binary_tree.get_morse(None, 'h') 
def test_encode_new_chars(self):
    self.assertEqual(morse.encode('()+-,?&!;'), '-.--.|-.--.-|.-.-.|-....-|--..--|..--.|.-...|-.-.--|-.-.-.|') #Pass -Test for new characters
```
Similarly to the encode tests these decode tests check that the strings are correctly converted, this time from morse to ascii and that multiple morse words are translated. Again checking the error handling of the program and testing of new characters has also been carried out.
```python
def test_decode_us(self):
    self.assertEqual(morse.decode('..-|...|'), 'US') #Pass - Correct decoding
def test_decode_et(self):
    self.assertEqual(morse.decode('.|-|'), 'ET') #Pass - Correct decoding
def test_decode_sentence(self):
    self.assertEqual(morse.decode('-|.|...|-| ...|.|-.|-|.|-.|-.-.|.|'), 'TEST SENTENCE') #Pass - Correct deecoding
def test_decode_fail_us(self):
    self.assertEqual(morse.decode('..-|'), 'u') #Pail - Decode returns capitalised ascii therefore not equal
def test_decode_exception1(self):
    with self.assertRaises(ValueError): #Pass - Input too long - Program handles the intentional fail correctly
        morse.decode('..---------|...|') 
def test_decode_exception2(self):
    with self.assertRaises(ValueError):
        morse.decode('Hello') #Pass - Invalid string - Program handles the intentional fail correctly
def test_decode_new_chars(self):
    self.assertEqual(morse.decode('-.--.|-.--.-|.-.-.|-....-|--..--|..--.|.-...|-.-.--|-.-.-.|'), '()+-,?&!;') #Pass - Test for new characters
```
The last set of tests within morseunit.py tested against the tree's functionality, these test whether the trees have been built and populated correctly, this includes empty nodes and their error handling should they be hit.
```python
def test_tree_build_ascii(self):
    self.assertIsNotNone(morse.binary_tree.populate_ascii(tree, "E", ".")) #Pass - Check the insert function for ASCII
def test_tree_get_ascii(self):
    self.assertEqual(binary_tree.get_ascii(tree,'.'),'E') #Pass - Test the find function for Ascii
def test_tree_build_morse(self):
    self.assertIsNotNone(morse.binary_tree.populate_morse(tree)) #Pass - Check the insert function for Morse
def test_tree_get_morse(self):
    self.assertEqual(binary_tree.get_morse(tree,'E'),'.') #Pass - Test the find function for Morse
def test_tree_not_empty(self):
    self.assertIsNotNone(morse.decode('.')) #Pass - Check that tree is not empty 
def test_tree_empty_node(self):
    with self.assertRaises(ValueError):
        morse.decode('..--') #Pass - Check for an "empty" node    
```

Worksheet 2 - Part 2 Readme
============================

This section builds on the previous part of the worksheet, however instead of implementing a binary tree, a binary heap was to be implemented first, then further built on in task two using the ham radio syntax for morse code. Finally, in task three extending the program to communicate with a morse server.

Task 1- Binary Heap
-------------------
A binary heap is a data structure in the form of a binary tree, however all nodes are populated. As a binary heap is represented as an array this means that the 'x' node will reside in 'heap[x]', thus a left child can be accessed through 'heap[(2*x)]' and a right child via 'heap[(2*x)+1]'

The implmentation of my binary heap resides in 'heap.py', this consists of a single variable to be the heap:
```python
letter_heap = " ETIANMSURWDKGOHVF*L*PJBXCYZQ**54*3***2**+****16=/***(*7***8*90********************************************************:"
```


Along with a function to access the appropriate element of the heap. To begin with the function is called with a string, this is then checked to see if it ends with a space, if not then one needs to be added to end the string
```python
def heap_decode(msg):
    final =""
    index =1
    if not msg.endswith(" "):
        msg += " "
```
Next the function loops through the string, if a space is found then the end of a morse character has been identified and thus the index can be used to translate the character.The index is found by going "left" for a "." and "right" for a "-", incrementing based upon a left or right child (As previously discussed), once the appropriate index has been found this is then translated from the array.
```python
    for lm in msg:
        if lm == " ":
            final += letter_morse_heap[index-1]
            index = 1
        elif lm ==".":
            index= index*2
        elif lm == "-":
            index = (index*2)+1
        else:
            raise ValueError ("Invalid String")
    return final
```

Binary Tree vs Binary Heap vs Python Dictionary
-----------------------------------------------
Now that a heap had been implemented, it is important to discuss the difference in various data structures available to a programmer and why they might use one over another. 
Python dictionaries would be the simpliest way to implement the morse functionality. A dictionary is an array of keys and values, for morse these are dots and dashes which match to ascii characters. To use this for encoding and decoding with morse, the entire array would need to be indexed through in order to find the corresponding pair, then the character can be extracted and thus converted. Thus, the list's length correlates to the time taken to find the value, this can be represented as O(n).
```python
dictionary{".":"E", "-":"T"}
print (dictionary["."])
output: "E"
```
 Binary trees are more efficient than dictionaries, as the tree is ordered upon the first search you can already cut out half of the search options, then by following the appropriate branches, halving at each step, the required node can be found, the efficiency of this search method is O(log n). Alternatively, binary heaps can be used, this is also in the format of an array and as previously discussed specific indexes can be found using 'heap[(2*x)]' for the left child and a right child via 'heap[(2*x)+1]'. This shares the same O(log n) efficiency as a tree, however the code and computation resources are not as intensive. Out of these possible data structures, binary heaps are the most resource efficient but also remain relatively simple to implement. The difference between implementation has been demonstrated in both part 1 and part 2 of this worksheet.

Task 2 - Ham Radio
------------------
The Ham Radio extended notation includes both the sender and receiver within the morse code, this is done in the format of 'Receiver DE Sender Msg', the message is seperated from the meta data by an "=" and ended with "=(". This implementation was done within 'ham.py' and made use of the 'morse.py' from Worksheet 2 Part 1. 

To encode a message the user needs to call the 'ham_encode' function along with three arguments, the sender, recceiver and their message, they are then returned the output in morse. This function utilises the 'morse.encode' function, following the format of the ham radio conversation, the program stitches together all the required syntax and then passes it to 'morse.encode', this whole string is then 'uppered' encoded and returned.

```python
def ham_encode(sender,receiver,msg):
    check_input(sender,receiver,msg)
    return morse.encode(receiver + "DE" + sender +"="+ msg+"=(".upper())
```

The 'ham_decode' function required more time to implement, the user must call the function along with a message, they are then returned a tuple of the receiver, sender and decoded message. Firstly, the binary heap function is used to decode the entire message, this will include the ham radio notation.

```python
def ham_decode(msg):
    final =""
    index =1
    if not msg.endswith(" "):
        msg+= " "
    for lm in msg:
        if lm  ==".":
            index= index*2
        elif  lm  == "-":
            index = (index*2)+1
        elif lm == " ":
            final += letter_morse_heap[index-1]
            index = 1
        else:
            raise ValueError ("Invalid String")
```
Once the string has been fully decoded it must be split up into the two parts: meta data and message. The string is looped through checking if the character is an "=" if it is not them build up a new string, the first instance of an "=" will be the end of the meta data, thus all characters found up to this point are given to a new variable, and the string is reset so it can be built up again. 
```python
   i=0  
    split=""
    meta =""
    msge=""
    while i < len(final):
        if i+1 < len(final):
            if final[i] == "=" and final[i+1] != "(":
                meta += split
                split =""        
```
The message itself may contain an "=" thus it must be checked that the following character is a "(", if this is the case then it symbolises the end of the message and in a similar fashion, the string which had been built up is given to the new variable and the loop is broken out of. The else clause is where the current string gets built up.
```python
            elif final[i] == "=" and final[i+1] == "(":
                msge += split
                break
            else:
                split += final[i]
        i+=1
```
Finally, the meta data must be split up into receiver and sender, this is done through the split function on the 'DE' notation, the first element in the split array will be the receiver while the second element will be the sender; these are assigned to variables and along with the decoded message are returned from the function as a tuple.
```python
    rec = meta.split('DE')[0]
    send = meta.split('DE')[1]
    return rec, send, msge
```
It is important to check that the user's input into encode are also valid characters, this function uppers all the inputs and then loops through each character of each string against the 'letter_heap' if all letters are found then it will return cleanly, otherwise a value error will be raised from the word within which the character did not match.

```python
def check_input(sender,receiver,msg):
    sender =sender.upper()
    receiver=receiver.upper()
    msg = msg.upper()
    for lm in sender:
        if lm not in letter_heap:
            raise ValueError("Letter in Sender does not exist")
    for lm in receiver:
        if lm not in letter_heap:
            raise ValueError("Letter in Receiver does not exist")
    for lm in msg:
        if lm not in letter_heap:
            raise ValueError("Letter in Message does not exist")
    return 0
```
Task 3 - Morse Server
---------------------
This task is to develop an a program which communicates with the extended morse server, this was done in morseServer.py and by building on the first worksheet echo server. The core functionality had a few tweaks along with two functions implemented to interface with the server.
To run this task a user simply needs to run the program, they will then be prompted for a sender name along with a message, these will then be taken by the two new functions to return an echo server response and a time server response.

The main function received a few modifications, firstly the function was given a 'message' argument, this was so that outside functions could give different messages to the main function, which in turn uses it to 'send_message'. Next, the port which was being used needed to be updated to that of the extended morse server '10102. Finally, the message needed to be passed to send_message and the response would then both be printed out and returned to the calling function.

```python
async def main(message):
    uri = "ws://localhost:10102"
    async with websockets.connect(uri) as websocket:
        if message == "end":
            return 1
        clientid = json.loads(await websocket.recv())
        if clientid['type'] == 'join_evt':
            client_id = clientid['client_id']
        else:
            print("Did not receive a correct join message")
            return 0
        await send_message(websocket, message, client_id)
        response = await recv_message(websocket)
        print("Server response =", response)
        return response
```
Once the user has connected they then utilise 'send_message', this had to be updated so that the package had a type of 'morse_event', this aids the server in understanding the request.
```python
async def send_message(websocket, message, client_id):
    outward_message = {
        'client_id': client_id,
        'payload': message,
        'type': 'morse_evt'
    }
    await websocket.send(json.dumps(outward_message))
```

'Send_echo' is one of the new functions which was to be implemented, the requirements were that a user can enter a sender and message, that these then be encoded and sent to the server, then once the server responds the message is then decoded and displayed. To do this the function is called with both a sender and message, these variables along with the static "echo" are passed to the previously implemented 'ham_encode', this creates a ham radio morse string, this message is then passed into the main function where it is sent to the server, this will then return an echo response with the sender and receiver being reversed. This return is then decoded and printed out
```python
def send_echo(sender, message):
    print("Sending Echo Message")
    message = ham_encode(sender,"echo", message)
    decoded = ham_decode(asyncio.run(main(message)))
    print("Sender:",decoded[1], "\nReceiver:", decoded[0], "\nMessage:", decoded[2])
    return decoded
```
'Send_Time' fulfils the second requirement, the function works in the same fashion as 'send_echo' however, only a sender is required and this time both the receiver and message are hardcoded into the encode function "time" and "hello world", the remaining functionality is that of 'send_echo' as previously described. One addition that was required was a ":" to be placed within 'letter_heap' in the 57th position, this was due to the server returning the time in this format and this character was not accounted for until this stage.
```python
def send_time(sender):
    print("Sending Time Message")
    message = ham_encode( sender, "time","hello world")
    decoded = ham_decode(asyncio.run(main(message)))
    print("Sender:",decoded[1],"\nReceiver:", decoded[0], "\nTime:", decoded[2])
    return decoded
```

Part 2 - Unit Testing
---------------------
Further unit testing was required for all the new functionality, these tests were created in unitTests.py, each block tested one task of the second part to this worksheet:Heap tests, Ham tests and Morse server tests.

The heap tests are similar to that of the decode tests within part 1, they check for correct decoding of words and sentences along with appropriate error handling of non-morse characters being given as an input.
Heap Tests
```python
def test_heap_decode_us(self):
        self.assertEqual(heap.heap_decode('..- ...'), 'US') #Pass - Correct decoding
    def test_heap_decode_et(self):
        self.assertEqual(heap.heap_decode('. -'), 'ET') #Pass - Correct encoding
    def test_heap_decode_sentence(self):
        self.assertEqual(heap.heap_decode('- . ... -  ... . -. - . -. -.-. .'), 'TEST SENTENCE') #Pass - Correct encoding
    def test_heap_decode_fail_us(self):
        self.assertNotEqual(heap.heap_decode('..-'), 'us') #Pass - Test designed to fail - Not given appropriate morse to match
    def test_heap_decode_exception(self):
        with self.assertRaises(ValueError): #Pass - Errors when non-morse input is given
            heap.heap_decode('??')
```
Considering the Ham decode functionality was based upon that of the heap, these tests only needed to be changed to check for the new syntax. The error handling remained the same for invalid characters. The encode function heavily relied upon the encode function in part 1, thus the testing required was only for that of the new functionality which checked that the strings were being joined together correctly. Lastly, the 'check_input' function was tested to ensure that there was appropriate validation of user input and errors were raised when incorrect input was received.
```python
 def test_ham_decode_us(self):
        self.assertEqual(ham.ham_decode('.-. .---- -.. . ... .---- -...- .... .. -...- -.--. '),('R1', 'S1', 'HI')) #Pass - Correct decoding
    def test_ham_decode_exception(self):
        with self.assertRaises(ValueError): #Pass - Errors when non-morse input is given
            ham.ham_decode('??')
    def test_ham_decode_fail_us(self):
        self.assertNotEqual(ham.ham_decode('.-. .---- -.. . ... .---- -...- .... .. -...- -.--.'), 'us') #Pass - Test designed to fail - Not given appropriate morse to match
    def test_ham_encode_HI(self):
         self.assertEqual(ham.ham_encode('R1', 'S1', 'HI'),'... .---- -.. . .-. .---- -...- .... .. -...- -.--. ') #Pass - Correct decoding
    def test_check_input(self):
        with self.assertRaises(ValueError): #Pass - Errors when non-morse input is given
            ham.check_input('??')
```
With the functionality of the server program extending the previous implementations, testing was needed for the specific server interactions. 'send_echo' was tested to ensure that the response had returned from the server in the correct tuple format. 'send_time' was tested to check that the server sent back a time, that it was correct and also that the function handled this in the expected manner. To do this 'datetime' was imported so that the test program could grab the current time, this was then compared to the server's time along with the remaining tuple.
```python
  def test_server_echo(self):
        self.assertEqual(morseServer.send_echo('S1', 'Hello'),('S1', 'ECHO', 'HELLO')) #Pass - Correct encoding, sending and decoding
    def test_server_echo_Fail(self):
        self.assertNotEqual(morseServer.send_echo('S1', 'Hello'),'... .---- -.. . . -.-. .... --- -...- .... . .-.. .-.. --- -...- -.--. -...- -.--.') #Pass -Designed to fail- Program decodes instead of returns morse
    def test_server_time(self):
        now = datetime.now()
        current_time = now.strftime("%H:%M:%S")
        self.assertEqual(morseServer.send_time('S1'),('S1', 'TIME', current_time)) #Pass - Correct encoding, sending and decoding along with time matching
    def test_server_echo_Fail2(self):
        self.assertNotEqual(morseServer.send_time('S1'),'... .---- -.. . . -.-. .... --- -...- .... . .-.. .-.. --- -...- -.--. -...- -.--.') #Pass -Designed to fail- Program decodes instead of returns morse        
```