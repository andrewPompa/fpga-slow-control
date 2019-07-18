import falcon
import json


class ConfigurationResource(object):
    def __init__(self, config_file_path):
        self.config_file_path = config_file_path

    def validate_request_headers(req, resp, resource, params):
        if req.content_type != "application/json":
            msg = 'Request payload has to be json!'
            raise falcon.HTTPBadRequest('Bad request', msg)

    @falcon.before(validate_request_headers)
    def on_put(self, req, resp):
        print "PUT REQUEST"
        try:
            configuration = json.loads(req.stream.read())
        except ValueError, e:
            print e
            resp.status = falcon.HTTP_500
            resp.data = "{\"error\": 'cannot parse configuration file'}"
            return
        print configuration
        try:
            f = open(self.config_file_path, 'w+')
        except IOError:
            print "cannot open config file"
            resp.data = "{\"error\": 'cannot open config file'}"
            resp.status = falcon.HTTP_500
            return
        json.dump(configuration, f)
        f.close()
        resp.status = falcon.HTTP_200

    def on_get(self, req, resp, uuid):
        print uuid
        resp.content_type = "application/json"
        try:
            f = open(self.config_file_path, 'r')
            configuration = json.load(f)
        except IOError:
            print "config not set yet"
            resp.status = falcon.HTTP_404
            return
        except ValueError:
            print "cannot parse to json"
            resp.data = "{\"error\": 'cannot parse configuration file'}"
            resp.status = falcon.HTTP_500
            return
        f.close()
        resp.media = configuration
        resp.status = falcon.HTTP_200
