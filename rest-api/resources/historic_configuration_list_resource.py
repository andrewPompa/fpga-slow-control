import falcon
import json
import datetime


class HistoricConfigurationListResource(object):
    def __init__(self, historic_configuration_service, inactive_historic_configuration_service):
        self.inactive_historic_configuration_service = inactive_historic_configuration_service
        self.historic_configuration_service = historic_configuration_service

    def on_get(self, req, resp):
        print "HistoricConfigurationListResource GET REQUEST"
        try:
            configurations = self.historic_configuration_service.find_valid_files()
            inactive_configurations = self.inactive_historic_configuration_service.find_valid_files()
        except OSError:
            resp.data = json.dumps({"error": 'cannot open folder with configurations'})
            resp.status = falcon.HTTP_500
            return
        configurations_info = map(
            lambda configuration: self.map_to_active_configuration_info(configuration),
            configurations
        )
        inactive_configurations_info = map(
            lambda configuration: self.map_to_inactive_configuration_info(configuration),
            inactive_configurations
        )
        configurations_info += inactive_configurations_info
        resp.data = json.dumps(configurations_info)
        resp.status = falcon.HTTP_200

    def map_to_active_configuration_info(self, configuration):
        print configuration
        conf_json = self.historic_configuration_service.get_json_by_uuid(configuration)
        now = datetime.datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
        return {
            "uuid": configuration.split("_")[0],
            "creationDate": configuration.split("_")[1].split('.')[0],
            "toDate": now,
            "name": conf_json['name'],
            "isActive": True
        }

    def map_to_inactive_configuration_info(self, configuration):
        conf_json = self.inactive_historic_configuration_service.get_json_by_uuid(configuration)
        return {
            "uuid": configuration.split("_")[0],
            "creationDate": configuration.split("_")[1],
            "toDate": configuration.split("_")[2].split('.')[0],
            "name": conf_json['name'],
            "isActive": False
        }
