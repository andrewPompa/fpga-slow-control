import datetime
from threading import Timer


class HistoricDataGathererJob(object):
    def __init__(self, interval_seconds, configuration_cache, memory_service, historic_data_file_writer):
        self.historic_data_file_writer = historic_data_file_writer
        self.memory_service = memory_service
        self.interval_seconds = interval_seconds
        self.configuration_cache = configuration_cache

    def start(self):
        t = Timer(self.interval_seconds, self.execute)
        t.start()

    def execute(self):
        now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print 'job started at: ' + now

        self.configuration_cache.for_each(self.gather_data)

        t = Timer(self.interval_seconds, self.execute)
        t.start()

    def gather_data(self, key, value):
        now = datetime.datetime.now()
        next_time = value['next_execution_time']
        if value['next_execution_time'] <= now:
            word = self.memory_service.get_as_base64(value['address'], 1)
            self.historic_data_file_writer.add({'file': key, 'word': word, 'time': now.strftime("%Y-%m-%d %H:%M:%S")})
            next_time += datetime.timedelta(milliseconds=value['interval'])
        return next_time
