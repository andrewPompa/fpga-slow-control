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
            self.cache = self.create_cache()
            print 'cache loaded'
            print self.cache
        finally:
            self.mutex.release()

    def create_cache(self):
        configurations = self.historic_data_service.find_valid_files()
        cache = {}
        for configuration in configurations:
            conf_json = self.historic_data_service.get_json_by_uuid(configuration)
            now = datetime.datetime.now()
            for chart in conf_json['charts']:
                file_name = configuration.split('_')[0] + '_' + str(chart['id']) + '_timeline.dat'
                data = {'type': 'timeline', 'interval': int(chart['interval']), 'next_execution_time': now}
                cache[file_name] = data
                for series in chart['series']:
                    file_name = configuration.split('_')[0] + '_' + str(chart['id']) + '_' + str(series['id']) + '.dat'
                    data = {'type': 'value', 'address': int(series['address'], 16), 'interval': int(chart['interval']), 'next_execution_time': now}
                    cache[file_name] = data
        return cache

    def reload(self):
        new_cache = self.create_cache()
        self.mutex.acquire()
        try:
            for key in new_cache:
                if key in self.cache:
                    new_cache[key] = self.cache[key]
            self.cache = new_cache
            print 'cache reloaded'
            print self.cache
        finally:
            self.mutex.release()

    def for_each(self, execute_and_calculate_next_time):
        self.mutex.acquire()
        try:
            for key in self.cache:
                self.cache[key]['next_execution_time'] = execute_and_calculate_next_time(key, self.cache[key])
        finally:
            self.mutex.release()
