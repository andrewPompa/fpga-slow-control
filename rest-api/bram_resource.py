import re
from base64 import b64encode, b64decode

import falcon

from subprocess import check_call, check_output, Popen, PIPE


class BramResource(object):
    def validate_request_headers(req, resp, resource, params):
        if req.content_type != "application/octet-stream":
            msg = 'Request payload has to be binary data!'
            raise falcon.HTTPBadRequest('Bad request', msg)

    @staticmethod
    def validate_and_get_parameters(query_string, address):
        if re.search(r"words=\d+", query_string) is None:
            raise falcon.HTTPBadRequest('Bad request', "Num of words has to be specified")

        try:
            address_number = int(address)
        except ValueError:
            raise falcon.HTTPBadRequest('Bad request', "Address has to be a number")

        return query_string.split("=")[1], str(address_number)

    @staticmethod
    def get_encoded_data_to_write(data_stream, data_length):
        data = data_stream.read(data_length or 0)
        if data == 0:
            raise falcon.HTTPBadRequest('Bad request', "Data stream not provided")
        return b64encode(data)

    @falcon.before(validate_request_headers)
    def on_patch(self, req, resp, address):
        num_of_words, address_str = self.validate_and_get_parameters(req.query_string, address)
        words = self.get_encoded_data_to_write(req.stream, req.content_length)
        print words
        response = check_call(["./bram_controller", "-s", "-w", address_str, num_of_words, words])
        print "response is = " + str(response)
        resp.status = falcon.HTTP_200

    def on_get(self, req, resp, address):
        num_of_words, address_str = self.validate_and_get_parameters(req.query_string, address)
        bram_bytes = check_output(["./bram_controller", "-s", "-r", address_str, num_of_words], stdin=PIPE)
        resp.content_type = "application/octet-stream"
        print "bram_bytes = " + bram_bytes
        resp.data = b64decode(bram_bytes)
        resp.status = falcon.HTTP_200
