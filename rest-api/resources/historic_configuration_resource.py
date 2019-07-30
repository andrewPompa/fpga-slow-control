import falcon
import json
import datetime


class HistoricConfigurationResource(object):
    def __init__(self, historic_configuration_service, configuration_cache):
        self.historic_configuration_service = historic_configuration_service
        self.historic_configuration_service.create_directory_in_configuration_path("/inactive")
        self.configuration_cache = configuration_cache

    def validate_request_headers(req, resp, resource, params):
        if req.content_type != "application/json":
            msg = 'Request payload has to be json!'
            raise falcon.HTTPBadRequest('Bad request', msg)

    def on_get(self, req, resp, uuid_value):
        resp.content_type = "application/json"
        try:
            json_configuration = self.historic_configuration_service.get_file_by_uuid(uuid_value)
        except OSError:
            resp.data = json.dumps({"error": 'cannot open folder with configurations'})
            resp.status = falcon.HTTP_500
            return
        except ValueError:
            resp.data = json.dumps({"error": 'cannot parse configuration file'})
            resp.status = falcon.HTTP_500
            return
        if json_configuration is None:
            resp.status = falcon.HTTP_204
            return
        resp.media = json_configuration
        resp.status = falcon.HTTP_200

    @falcon.before(validate_request_headers)
    def on_post_new_configuration(self, req, resp):
        file_id = self.historic_configuration_service.generate_new_file_id()
        now = datetime.datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
        try:
            json_configuration = json.loads(req.stream.read())
            self.historic_configuration_service.save_file(file_id, now, json_configuration)
            resp.data = json.dumps({"uuid": str(file_id)})
            resp.status = falcon.HTTP_201
            self.configuration_cache.load_cache()
        except OSError:
            resp.data = json.dumps({"error": 'cannot open folder with configurations'})
            resp.status = falcon.HTTP_500
        except ValueError:
            resp.data = json.dumps({"error": 'cannot parse configuration file'})
            resp.status = falcon.HTTP_500
        except NameError:
            resp.data = json.dumps({"error": 'invalid name: ' + json_configuration["name"]})
            resp.status = falcon.HTTP_500

    def on_delete(self, req, resp, uuid_value):
        if self.historic_configuration_service.is_file_exists(uuid_value) is False:
            resp.status = falcon.HTTP_404
            return
        self.historic_configuration_service.delete_file(uuid_value)
        self.configuration_cache.load_cache()
