from tree import *

################################################
# Function Name : encode
# Returns    : e
# Args       : string
#
# Created by    : Daniel Carter
# Date created  : 21//02/21
# Description   : This function takes a string, it then populates an ascii tree. It will seperate the string into words
#and pass control to get_morse so that the string can be encoded.
################################################

def encode(string):
    ascii_root = binary_tree('ASCII')
    for char in letter_morse:
        ascii_tree =binary_tree.populate_ascii(ascii_root, char[0],char[1])
    #binary_tree.print_tree(ascii_tree,0)
    string = string.upper()
    e=""
    for char in string: 
        #Splitting the string into words
        if char == " ":
            e += " "
        else:
            #Passing each letter to get encoded and then split with "|"
            e += binary_tree.get_morse(ascii_tree,char)+ " "
    #print(e)
    return e    

################################################
# Function Name : decode
# Returns    : d
# Args       : string
#
# Created by    : Daniel Carter
# Date created  : 22//02/21
# Description   : This function takes a string and then populates a morse tree. It will split the
# morse into words and remove the character seperators "|. Control will be passed to get_ascii once a 
#morse character has been found.
################################################
def decode(string):
    morse_root = binary_tree('MORSE')
    morse_tree = binary_tree.populate_morse(morse_root)
    #binary_tree.print_tree(morse_tree,0)
    deliminated=""
    d=""
    #If the end of the string doesn't have a morse seperator add one
    if (string[len(string)-1]) != "|":
        string +="|"
    for char in string:
        #Split the string into words
        if char == " ":
            d+= " "
        #If a character is found add it to the search string
        elif char != "|":
            deliminated += char
            #If the string is longer than the tree is deep it is erroneous 
            if len(deliminated)>6:
                raise ValueError ("String too long")
        else:
            #Once the end of a morse character is found then translate it
            d += binary_tree.get_ascii(morse_tree,deliminated)
            deliminated = ""
    print("Decoded string:",d)
    return d