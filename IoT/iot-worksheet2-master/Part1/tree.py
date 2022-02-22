letter_morse = [("E", "."),("T","-"),("I",".."),("A",".-"),("N","-."),("M","--"),("S","..."),("U","..-"),("R",".-."),("W",".--"),("D","-.."),("K","-.-"),("G","--."),("O","---"),
("H","...."),("V","...-"),("F","..-."),("Empty","..--"),("L",".-.."),("Empty",".-.-"),("P",".--."),("J",".---"),("B","-..."),("X","-..-"),("C","-.-."),("Y","-.--"),("Z","--.."),("Q","--.-"),("Empty","---."),("Empty","----"),
("5","....."),("4","....-"),("Empty","...-."),("3","...--"),("Empty","..-.."),("¿","..-.-"),("?","..--."),("2","..---"),("&",".-..."),("Empty",".-..-"),("+",".-.-."),("Empty",".-.--"),("*",".--.."),("Empty",".--.-"),("Empty",".---."),("1",".----"),("6","-...."),("=","-...-"),("/","-..-."),("Empty","-..--"),("Empty","-.-.."),("Empty","-.-.-"),("(","-.--."),("Empty","-.---"),("7","--..."),("Empty","--..-"),("Empty","--.-."),("Empty","--.--"),("8","---.."),("Empty","---.-"),("9","----."),("0","-----"),
("Empty","......"),("Empty",".....-"),("Empty","....-."),("Empty","....--"),("Empty","...-.."),("Empty","...-.-"),("Empty","...--."),("Empty","...---"),("Empty","..-..."),("Empty","..-..-"),("Empty","..-.-."),("Empty","..-.--"),("Empty","..--.."),("_","..--.-"),("Empty","..---."),("Empty","..----"),("Empty",".-...."),("Empty",".-...-"),('"',".-..-."),("Empty",".-..--"),("Empty",".-.-.."),(".",".-.-.-"),("Empty",".-.--."),("Empty",".-.---"),("Empty",".--..."),("Empty",".--..-"),("Empty",".--.-."),("Empty",".--.--"),("Empty",".---.."),("Empty",".---.-"),
("'",".----."),("Empty",".-----"),("Empty","-....."),("-","-....-"),("Empty","-...-."),("Empty","-...--"),("Empty","-..-.."),("Empty","-..-.-"),("Empty","-..--."),("Empty","-..---"),("Empty","-.-..."),("Empty","-.-..-"),(";","-.-.-."),("!","-.-.--"),("Empty","-.--.."),(")","-.--.-"),("Empty","-.---."),("Empty","-.----"),("Empty","--...."),("¡","--...-"),("Empty","--..-."),(",","--..--"),("Empty","--.-.."),("Empty","--.-.-"),("Empty","--.--."),("Empty","--.---"),(":","---...")]

################################################
# Class : binary_tree
# Returns    : N/A
# Args       : N/A
#
# Created by    : Daniel Carter
# Date created  : 17//02/21
# Description   : Class to create, populate and search a binary tree
################################################

class binary_tree():
    def __init__(self, rootID):
        self.left = None
        self.right = None
        self.rootID = rootID
################################################
# Function Name : print_tree
# Returns    : N/A
# Args       : tree, depth
#
# Created by    : Daniel Carter
# Date created  : 17//02/21
# Description   : This function takes an instance of a binary tree, along with a
# depth for indentation, then prints out the entire tree
################################################

    def print_tree(tree, depth):
        if tree != None:
            for i in range(depth):
                print(' ', end ='')
            print(tree.rootID)
            binary_tree.print_tree(tree.left, depth+1)
            binary_tree.print_tree(tree.right, depth+1)

################################################
# Function Name : populate_ascii
# Returns    : self
# Args       : self, letter, morse
#
# Created by    : Daniel Carter
# Date created  : 18//02/21
# Description   : This function takes a self along with letter and morse. The tree is then
# populated based upon the ascii value and inserts both letter and morse into the appropriate node
################################################
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
            else:
                self.rootID= (letter, morse)
                return self

################################################
# Function Name : populate_morse
# Returns    : self
# Args       : tree, depth
#
# Created by    : Daniel Carter
# Date created  : 18//02/21
# Description   : This function takes a self, it will work through the tuples of letter_morse and insert them
# top to bottom and left to right into nodes which are empty along the way.
################################################
    def populate_morse(self):
        current = self
        newRow= []
        for char in letter_morse:
            if current.left == None:
                current.left = binary_tree(char)
            else:
                if current.right == None:
                    current.right = binary_tree(char)
                else:
                    #This realises the end of a row so moves down and inserts into first node left
                    newRow.append(current.left)
                    newRow.append(current.right)
                    current = newRow.pop(0)
                    current.left = binary_tree(char)
        return self

################################################
# Function Name : get_ascii
# Returns    : final
# Args       : tree, depth
#
# Created by    : Daniel Carter
# Date created  : 19//02/21
# Description   : This function takes a self and a string, this string is iterated through to return an ascii value.
# It searches left and right depending on the current morse character and once the node is found will add the ascii to the return string
################################################
    def get_ascii(self, string):
        current = self
        final = ""
        current = self
        for char in string:
            if char == ".":
                current = current.left
            elif char == "-":
                current = current.right
            else:
                raise ValueError("Invalid String")
        if current.rootID[0] == "Empty":
                raise ValueError ("Empty node found")
        else:
            final += current.rootID[0]
        return final

################################################
# Function Name : get_morse
# Returns    : morse_output
# Args       : self, char
#
# Created by    : Daniel Carter
# Date created  : 20//02/21
# Description   : This function takes a self and char, it will then evaluate the ascii value against the root value
# if they match it will return the morse otherwise it will return to itself either left or right to continue searching
################################################
    def get_morse(self, char):
        morse_output=""
        if self == None:
            raise ValueError ("No such letter")
        else:
            if char < self.rootID[0]:
                return  binary_tree.get_morse(self.left,char)
            elif char > self.rootID[0]:
                return binary_tree.get_morse(self.right,char)
            else:
                morse_output = self.rootID[1]
        return morse_output