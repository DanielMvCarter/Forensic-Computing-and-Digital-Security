import unittest
import UDP


class TestFiles(unittest.TestCase):
    def test_checksum(self):
        so_port= 0 
        de_port = 542 
        self.assertEqual(UDP.compute_checksum(so_port.to_bytes(2, "little"),de_port.to_bytes(2, "little"), b"1111"),(29595)) #Pass - Compute checksum is correct
    def test_checksum_fail(self):
        so_port= 0 
        de_port = 542 
        self.assertNotEqual(UDP.compute_checksum(so_port.to_bytes(2, "little"),de_port.to_bytes(2, "little"), b"1111"),(1)) #Pass - Compute checksum is incorrect
    def test_checksum2(self):
        so_port= 10
        de_port = 42 
        self.assertEqual(UDP.compute_checksum(so_port.to_bytes(2, "little"),de_port.to_bytes(2, "little"), b"Welcome to IoT UDP Server"),(15307)) #Pass - Compute checksum is correct    
        
if __name__ == '__main__':
    unittest.main()