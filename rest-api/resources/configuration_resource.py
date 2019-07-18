import falcon
import json
import datetime


class ConfigurationResource(object):
    def __init__(self, file_name_service):
        self.file_name_service = file_name_service

    def validate_request_headers(req, resp, resource, params):
        if req.content_type != "application/json":
            msg = 'Request payload has to be json!'
            raise falcon.HTTPBadRequest('Bad request', msg)

    def on_get(self, req, resp, uuid_value):
        resp.content_type = "application/json"
        try:
            json_configuration = self.file_name_service.get_file_by_uuid(uuid_value)
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
    def on_post_add_configuration(self, req, resp):
        file_id = self.file_name_service.generate_new_file_id()
        today = datetime.date.today().strftime("%Y%m%d")
        try:
            json_configuration = json.loads(req.stream.read())
            self.file_name_service.save_file(file_id, today, json_configuration)
            resp.data = json.dumps({"uuid": str(file_id)})
            resp.status = falcon.HTTP_201
        except OSError:
            resp.data = json.dumps({"error": 'cannot open folder with configurations'})
            resp.status = falcon.HTTP_500
        except ValueError:
            resp.data = json.dumps({"error": 'cannot parse configuration file'})
            resp.status = falcon.HTTP_500
        except NameError:
            resp.data = json.dumps({"error": 'invalid name: ' + json_configuration["name"]})
            resp.status = falcon.HTTP_500


    @falcon.before(validate_request_headers)
    def on_put(self, req, resp, uuid_value):
        resp.content_type = "application/json"
        json_configuration = None
        if self.file_name_service.is_file_exists(uuid_value) is False:
            resp.status = falcon.HTTP_204
            return

        try:
            json_configuration = json.loads(req.stream.read())
            self.file_name_service.update_file(uuid_value, json_configuration)
            updated_json = self.file_name_service.get_file_by_uuid(uuid_value)
            resp.media = updated_json
            resp.status = falcon.HTTP_200
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
        if self.file_name_service.is_file_exists(uuid_value) is False:
            resp.status = falcon.HTTP_404
            return
        self.file_name_service.delete_file(uuid_value)
