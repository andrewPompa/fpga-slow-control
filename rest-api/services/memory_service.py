from base64 import b64encode
from subprocess import check_output, PIPE, check_call


class MemoryService(object):
    def __init__(self, bram_file_path):
        self.bram_file_path = bram_file_path

    def get_as_base64(self, address, num_of_words):
        memory_bytes = check_output([self.bram_file_path, "-s", "-r", str(address), str(num_of_words)], stdin=PIPE)
        return memory_bytes

    def put_from_base64(self, address, num_of_words, encoded_base64_words):
        response = check_call([self.bram_file_path, "-s", "-w", str(address), str(num_of_words), encoded_base64_words])
        return response
