import os


class HistoricDataService(object):
    def __init__(self, historic_data_directory):
        self.historic_data_directory = historic_data_directory

    def remove_all(self, uuid_value):
        files = os.listdir(self.historic_data_directory)
        filtered_files = filter(lambda config: config.startswith(uuid_value), files)
        if filtered_files is None or len(filtered_files) == 0:
            print "not filtered properly"
            return None
        for file_to_delete in filtered_files:
            os.remove(self.historic_data_directory + file_to_delete)

    def get_value_for_chart(self, uuid_value, chart_id):
        timeline = self.get_timeline(uuid_value, chart_id)
        series = self.find_series(uuid_value, chart_id)
        if timeline is None or series is None:
            return None
        return {'layouts': timeline, 'series': series}

    def get_timeline(self, uuid_value, chart_id):
        timeline_file = self.find_file(uuid_value + '_' + chart_id + "_timeline.dat")
        if timeline_file is None:
            return None
        try:
            f = open(self.historic_data_directory + timeline_file, 'r')
            timeline = f.read().split(',')
            timeline.remove('')
        except IOError, e:
            print "cannot open file", e
            return None
        f.close()
        return timeline

    def find_series(self, uuid_value, chart_id):
        series = {}
        files = self.find_file_with_name_starts(uuid_value + '_' + chart_id)
        for series_file in files:
            if series_file.find('timeline') != -1:
                continue
            try:
                f = open(self.historic_data_directory + series_file, 'r')
                values = f.read().split(',')
                values.remove('')
            except IOError, e:
                print "cannot open file", e
                return None
            series_id = series_file.split('_')[2].split('.')[0]
            series[series_id] = values
        return series

    def find_file(self, file_name):
        files = os.listdir(self.historic_data_directory)
        searched_file = filter(lambda data_file: data_file == file_name, files)
        if searched_file is None or len(files) == 0:
            return None
        return searched_file[0]

    def find_file_with_name_starts(self, starts_with):
        files = os.listdir(self.historic_data_directory)
        searched_files = filter(lambda data_file: data_file.startswith(starts_with), files)
        if searched_files is None or len(searched_files) == 0:
            return None
        return searched_files
