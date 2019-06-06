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
        words, address_str = self.validate_and_get_parameters(req.query_string, address)
        data = self.get_encoded_data_to_write(req.stream, req.content_length)
        response = check_call(["./bram-rest", "-w", address_str, words, data])
        resp.status = falcon.HTTP_200

    def on_get(self, req, resp, address):
        words, address_str = self.validate_and_get_parameters(req.query_string, address)
        bram_bytes = check_output(["./bram-rest", "-r", address_str, words], stdin=PIPE)
        resp.content_type = "application/octet-stream"
        resp.data = bram_bytes
        # resp.data = b64decode(bram_bytes)
        resp.status = falcon.HTTP_200
