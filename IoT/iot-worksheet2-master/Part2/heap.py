letter_morse_heap = " ETIANMSURWDKGOHVF*L*PJBXCYZQ**54*3***2**+****16=/***(*7***8*90"

################################################
# Function Name :heap_decode
# Returns    : final
# Args       : msg
#
# Created by    : Daniel Carter
# Date created  : 22//03/21
# Description   : This function takes a message, and coverts it to ascii this is done by accessing an array based upon a left
#or right child, once the appropriate index has been found this is then translated from the array.
################################################
def heap_decode(msg):
    final =""
    index =1
    if not msg.endswith(" "):
        msg += " "
    for lm in msg:
        #If the end of a letter is found then convert through index
        if lm == " ":
            # index-1 due to arrays starting at 0
            final += letter_morse_heap[index-1]
            index = 1
        #Find left child
        elif lm ==".":
            index= index*2
        #Find right child
        elif lm == "-":
            index = (index*2)+1
        #Invalid character in string
        else:
            raise ValueError ("Invalid String")
    return final

#print(heap_decode(".-. .---- -.. . ... .---- -...- .... .. -...- -.--."))