import os
import re

import falcon
import json


class ConfigurationListResource(object):
    def __init__(self, configuration_file_directory):
        self.configuration_file_directory = configuration_file_directory
        self.file_name_regex = re.compile("^[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+_\d{8}_\w+\.json$")

    def on_get(self, req, resp):
        print "ConfigurationListResource GET REQUEST"
        try:
            configurations = os.listdir(self.configuration_file_directory)
        except OSError, e:
            print "cannot open folder with configurations: ", e
            resp.data = json.dumps({"error": 'cannot open folder with configurations'})
            resp.status = falcon.HTTP_500
            return
        configurations = filter(lambda config: re.match(self.file_name_regex, config), configurations)
        configurations_info = map(
            lambda conf: {"uuid": conf.split("_")[0], "creation_date": conf.split[1], "name": conf.split[2][:-5]},
            configurations
        )
        resp.data = json.dumps(configurations_info)
        resp.status = falcon.HTTP_200
