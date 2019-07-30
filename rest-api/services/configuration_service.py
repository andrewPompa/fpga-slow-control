import json
import os
import re
import shutil
import uuid


class ConfigurationService(object):
    def __init__(self, configuration_file_directory, file_name_regex):
        self.configuration_file_directory = configuration_file_directory
        self.file_name_regex = file_name_regex

    def is_valid_file_name(self, file_name):
        return re.match(self.file_name_regex, file_name)

    def generate_new_file_id(self):
        return uuid.uuid4()

    def find_valid_files(self):
        try:
            configurations = os.listdir(self.configuration_file_directory)
        except OSError, e:
            print "cannot open folder with configurations: ", e
            raise
        return filter(lambda config: self.is_valid_file_name(config), configurations)

    def get_file_by_uuid(self, uuid_value):
        configurations = self.find_valid_files()
        configuration = filter(lambda config: config.startswith(uuid_value), configurations)
        if configuration is None or len(configuration) == 0:
            print "not filtered properly"
            return None
        configuration = configuration[0]
        return configuration

    def get_json_by_uuid(self, uuid_value):
        configurations = self.find_valid_files()
        configuration = filter(lambda config: config.startswith(uuid_value), configurations)
        if configuration is None or len(configuration) == 0:
            print "not filtered properly"
            return None
        configuration = configuration[0]
        try:
            f = open(self.configuration_file_directory + "/" + configuration, 'r')
            json_configuration = json.load(f)
        except (IOError, ValueError), e:
            print "this config not set yet ", e
            return None
        f.close()
        return json_configuration

    def is_file_exists(self, uuid_value):
        configurations = self.find_valid_files()
        configuration = filter(lambda config: config.startswith(uuid_value), configurations)
        if configuration is None or len(configuration) == 0:
            return False
        configuration = configuration[0]
        try:
            f = open(self.configuration_file_directory + "/" + configuration, 'r')
        except IOError, e:
            print "this config not set yet ", e
            return False
        f.close()
        return True

    def save_file(self, uuid_value, date, json_value):
        file_name = str(uuid_value) + "_" + date + ".json"
        if self.is_valid_file_name(file_name) is None:
            raise NameError
        try:
            f = open(self.configuration_file_directory + "/" + file_name, 'w+')
        except IOError, e:
            print "cannot open config file: ", e
            raise
        json.dump(json_value, f)
        f.close()

    def update_file(self, uuid_value, json_value):
        configurations = self.find_valid_files()
        configuration = filter(lambda config: config.startswith(uuid_value), configurations)
        if configuration is None or len(configuration) == 0:
            return
        configuration = configuration[0]
        try:
            f = open(self.configuration_file_directory + "/" + configuration, 'w')
        except IOError, e:
            print "this config not set yet ", e
            return
        json.dump(json_value, f)
        f.close()

    def delete_file(self, uuid_value):
        configurations = self.find_valid_files()
        configuration = filter(lambda config: config.startswith(uuid_value), configurations)
        if configuration is None or len(configuration) == 0:
            return
        configuration = configuration[0]
        os.remove(self.configuration_file_directory + "/" + configuration)

    def create_directory_in_configuration_path(self, directory_path):
        if not os.path.exists(self.configuration_file_directory + directory_path):
            os.mkdir(self.configuration_file_directory + directory_path)

    def move_to_subdirectory(self, file_name, subdirectory, new_file_name):
        file_path = self.configuration_file_directory + file_name
        new_file_path = self.configuration_file_directory + "/" + subdirectory + "/" + new_file_name
        os.rename(file_path, new_file_path)
