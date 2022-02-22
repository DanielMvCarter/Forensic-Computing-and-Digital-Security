import unittest
import morse
from tree import binary_tree

tree = binary_tree('root') 
class TestMorse(unittest.TestCase):

        ###############
        #Encode Tests##
        ###############

    def test_encode_us(self):
        self.assertEqual(morse.encode('us'), '..-|...|') #Pass - Correct encoding
    def test_encode_et(self):
        self.assertEqual(morse.encode('et'), '.|-|') #Pass - Correct encoding
    def test_encode_sentence(self):
        self.assertEqual(morse.encode('test sentence'), '-|.|...|-| ...|.|-.|-|.|-.|-.-.|.|') #Pass - Correct encoding
    def test_encode_fail_us(self):
        self.assertNotEqual(morse.encode('us'), '..-|') #Pass - Test designed to fail - Not given appropriate morse to match
    def test_encode_exception(self):
        with self.assertRaises(ValueError): #Pass - None tree is given therefore when looking in self value error is raised
            binary_tree.get_morse(None, 'h') 
    def test_encode_new_chars(self):
        self.assertEqual(morse.encode('()+-,?&!;'), '-.--.|-.--.-|.-.-.|-....-|--..--|..--.|.-...|-.-.--|-.-.-.|') #Pass -Test for new characters

        ################
        ##Decode Tests##
        ################

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

        ################
        ###Tree Tests###
        ################

   
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
            
if __name__ == '__main__':
    unittest.main()