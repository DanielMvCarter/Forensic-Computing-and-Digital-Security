import unittest
import heap
import ham
import morseServer
from datetime import datetime

class TestFiles(unittest.TestCase):

        #############
        #Heap Tests##
        #############

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

        #############
        ##Ham Tests##
        #############

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
            ham.check_input('??','~~','^^')

        ##################
        ###Server Tests###
        ##################

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

if __name__ == '__main__':
    unittest.main()