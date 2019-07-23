import re

import falcon
import ConfigParser
from interceptors.cors_interceptor import CORSInterceptor
from resources.memory_management_resource import MemoryManagementResource
from resources.configuration_resource import ConfigurationResource
from resources.configuration_list_resource import ConfigurationListResource
from resources.historic_configuration_resource import HistoricConfigurationResource
from services.configuration_service import ConfigurationService

configuration_name_regex = re.compile("^[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+_\d{8}\.json$")
historic_name_regex = re.compile("^[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+_\d{4}_\d{2}_\d{2}_\d{2}_\d{2}_\d{2}\.json$")

config = ConfigParser.ConfigParser()
config.read('server.cfg')
historic_configuration_file_directory = config.get('CONFIGURATION', 'historic_configuration_file_directory')
configuration_file_directory = config.get('CONFIGURATION', 'configuration_file_directory')
bram_controller_path = config.get('CONFIGURATION', 'bram_controller_path')
page_path = config.get('CONFIGURATION', 'page_path')

configuration_service = ConfigurationService(configuration_file_directory, configuration_name_regex)
historic_configuration_service = ConfigurationService(historic_configuration_file_directory, historic_name_regex)

bram = MemoryManagementResource(bram_controller_path)
configuration = ConfigurationResource(configuration_service)
historic_configuration = HistoricConfigurationResource(historic_configuration_service)
configuration_list = ConfigurationListResource(configuration_service)

api = application = falcon.API(middleware=[CORSInterceptor()])
api.add_route('/address/{address}', bram)

api.add_route('/configuration/all', configuration_list)
api.add_route('/configuration/{uuid_value}', configuration)
api.add_route('/configuration', configuration, suffix="add_configuration")

api.add_route('/historic-configuration/{uuid_value}', historic_configuration)
api.add_route('/historic-configuration', historic_configuration, suffix="new_configuration")

api.add_static_route('/', page_path, False, 'index.html')
