import datetime
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
            self.cache = {}
            for configuration in configurations:
                conf_json = self.historic_data_service.get_json_by_uuid(configuration)
                for chart in conf_json['charts']:
                    for series in chart['series']:
                        file_name = configuration.split('.')[0] + '_' + str(chart['id']) + '_' + str(series['id']) + '.dat'
                        now = datetime.datetime.now()
                        data = {'address': int(series['address'], 16), 'interval': int(chart['interval']), 'next_execution_time': now}
                        self.cache[file_name] = data
        finally:
            self.mutex.release()

    def for_each(self, execute_and_calculate_next_time):
        self.mutex.acquire()
        try:
            for key in self.cache:
                self.cache[key]['next_execution_time'] = execute_and_calculate_next_time(key, self.cache[key])
        finally:
            self.mutex.release()
