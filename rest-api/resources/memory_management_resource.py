import re
from base64 import b64encode

import falcon


class MemoryManagementResource(object):
    def __init__(self, memory_service):
        self.memory_service = memory_service

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
        response = self.memory_service.put_from_base64(address_str, num_of_words, words)
        print "patch is = " + response
        resp.status = falcon.HTTP_200

    def on_get(self, req, resp, address):
        print "GET"
        num_of_words, address_str = self.validate_and_get_parameters(req.query_string, address)
        response = self.memory_service.get_as_base64(address_str, num_of_words)
        print "response is = " + response

        resp.content_type = "text/plain"
        resp.data = response
        resp.status = falcon.HTTP_200
