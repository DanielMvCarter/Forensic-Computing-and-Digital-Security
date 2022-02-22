import morse
letter_heap = " ETIANMSURWDKGOHVF*L*PJBXCYZQ**54*3***2**+****16=/***(*7***8*90********************************************************:"

################################################
# Function Name : check_input
# Returns    : Value error/0
# Args       : string
#
# Created by    : Daniel Carter
# Date created  : 23//03/21
# Description   : Loops through the string passed in and checks if each character is within the heap
################################################

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

################################################
# Function Name : ham_encode
# Returns    : morse.encode
# Args       : sender, receiver, msg
#
# Created by    : Daniel Carter
# Date created  : 23//03/21
# Description   : This function takes a sender, receiver and message, joins them along with the ham radio
#syntax and then passes to encode function from Worksheet2 Part 1
################################################
def ham_encode(sender,receiver,msg):
    check_input(sender,receiver,msg)
    return morse.encode(receiver + "DE" + sender +"="+ msg+"=(".upper())

################################################
# Function Name :ham_decode
# Returns    : rec, send, msge
# Args       : msg
#
# Created by    : Daniel Carter
# Date created  : 23//03/21
# Description   : This function takes a message, and coverts it to ascii then splits it into meta data and message,
# based upon ham syntax, after this it splits the meta data down into sender and receiver.
################################################
def ham_decode(msg):
    final =""
    index =1
    if not msg.endswith(" "):
        msg+= " "
    #Iterate through message to gain a full converted string
    for lm in msg:
        if lm  ==".":
            index= index*2
        elif  lm  == "-":
            index = (index*2)+1
        elif lm == " ":
            final += letter_heap[index-1]
            index = 1
        else:
            raise ValueError ("Invalid String")
    i=0  
    split=""
    meta =""
    msge=""
    #Split converted string into meta and message
    while i < len(final):
        #Ensuring index is within range
        if i+1 < len(final):
            #Finds the first "=" in ham syntax, all data before is meta
            if final[i] == "=" and final[i+1] != "(":
                #Add and then reset split
                meta += split
                split =""
            #Remaining data is message
            elif final[i] == "=" and final[i+1] == "(":
                msge += split
                break
            #If not an "=" then build current working string
            else:
                split += final[i]
        i+=1
    #Split the meta data into receiver and sender based upon DE
    rec = meta.split('DE')[0]
    send = meta.split('DE')[1]
    return rec, send, msge

# print(ham_decode(".-. .---- -.. . ... .---- -...- .... .. -...- -.--. "))
# print(ham_encode("S1","R1","HI"))