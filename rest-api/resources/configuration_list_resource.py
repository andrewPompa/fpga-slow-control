import os
import re
import falcon
import json


class ConfigurationListResource(object):
    def __init__(self, file_name_service):
        self.file_name_service = file_name_service
        self.file_name_regex = re.compile("^[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+_\d{8}\.json$")

    def on_get(self, req, resp):
        print "ConfigurationListResource GET REQUEST"
        try:
            configurations = self.file_name_service.find_valid_files()
        except OSError:
            resp.data = json.dumps({"error": 'cannot open folder with configurations'})
            resp.status = falcon.HTTP_500
            return
        configurations_info = map(
            lambda configuration: self.map_to_configuration_info(configuration),
            configurations
        )
        resp.data = json.dumps(configurations_info)
        resp.status = falcon.HTTP_200

    def map_to_configuration_info(self, configuration):
        print configuration
        conf_json = self.file_name_service.get_json_by_uuid(configuration)
        return {"uuid": configuration.split("_")[0], "creationDate": configuration.split("_")[1].split('.')[0], "name": conf_json['name']}

