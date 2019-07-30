import Queue
from threading import Thread


class HistoricDataFileWriter(object):
    def __init__(self, historic_data_directory):
        self.historic_data_directory = historic_data_directory
        self.to_save_queue = Queue.PriorityQueue()

    def start(self):
        t = Thread(target=self.execute)
        t.start()

    def execute(self):
        while True:
            row = self.to_save_queue.get()
            with open(self.historic_data_directory + row['file'], "a+") as f:
                f.write(row['value'] + ',')
            self.to_save_queue.task_done()

    def add(self, sth):
        self.to_save_queue.put(sth)
