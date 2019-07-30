import random
from base64 import b64decode, b64encode


class MemoryMockService(object):
    def __init__(self, bram_file_path):
        self.bram_file_path = bram_file_path

    def get_as_base64(self, address, num_of_words):
        memory_value = []
        for i in range(4 * int(num_of_words)):
            memory_value.append(random.randint(0, 255))
        memory_value = bytearray(memory_value)
        # print 'memory value for address: ' + str(address) + ' is: ' + b64encode(memory_value)
        return b64encode(memory_value)

    def put_from_base64(self, address, num_of_words, decode_base64_words):
        response = 'ok'
        print 'response is = ' + str(response)