from threading import Lock


class ConfigurationCache(object):
    def __init__(self, historic_data_service):
        self.historic_data_service = historic_data_service
        self.mutex = Lock()
        self.cache = {}

    def load_cache(self):
        self.mutex.acquire()
        try:
            configurations = self.historic_data_service.find_valid_files()
            cache = {}
            for configuration in configurations:
                conf_json = self.historic_data_service.get_file_by_uuid(configuration)
                for chart in conf_json['charts']:
                    for series in chart['series']:
                        file_name = configuration.split('.')[0] + '_' + str(chart['id']) + '_' + str(series['id']) + '.json'
                        cache[file_name] = int(series['address'], 16)
        finally:
            self.mutex.release()
