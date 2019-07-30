import re
import time

import falcon
import ConfigParser
from interceptors.cors_interceptor import CORSInterceptor
from resources.memory_management_resource import MemoryManagementResource
from resources.configuration_resource import ConfigurationResource
from resources.configuration_list_resource import ConfigurationListResource
from resources.historic_configuration_resource import HistoricConfigurationResource
from resources.historic_configuration_list_resource import HistoricConfigurationListResource
from resources.historic_data_resource import HistoricDataResource
from services.configuration_cache import ConfigurationCache
from services.configuration_service import ConfigurationService
from services.memory_service import MemoryService
from services.memory_mock_service import MemoryMockService
from services.historic_data_gatherer_job import HistoricDataGathererJob
from services.historic_data_file_writer import HistoricDataFileWriter
from services.historic_data_service import HistoricDataService

configuration_name_regex = re.compile("^[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+_\d{8}\.json$")
historic_name_regex = re.compile("^[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+_\d{4}-\d{2}-\d{2}-\d{2}-\d{2}-\d{2}\.json$")
inactive_historic_name_regex = re.compile("^[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+-[a-z0-9]+(_\d{4}-\d{2}-\d{2}-\d{2}-\d{2}-\d{2}){2}\.json$")

config = ConfigParser.ConfigParser()
config.read('server.cfg')
historic_configuration_file_directory = config.get('CONFIGURATION', 'historic_configuration_file_directory')
configuration_file_directory = config.get('CONFIGURATION', 'configuration_file_directory')
bram_controller_path = config.get('CONFIGURATION', 'bram_controller_path')
page_path = config.get('CONFIGURATION', 'page_path')

historic_data_gatherer_interval_seconds = float(config.get('HISTORIC', 'interval_seconds'))
historic_data_directory = config.get('HISTORIC', 'data_directory')

configuration_service = ConfigurationService(configuration_file_directory, configuration_name_regex)
historic_configuration_service = ConfigurationService(historic_configuration_file_directory, historic_name_regex)
inactive_historic_configuration_service = ConfigurationService(historic_configuration_file_directory + 'inactive', inactive_historic_name_regex)
configuration_cache = ConfigurationCache(historic_configuration_service)
configuration_cache.load_cache()
memory_service = MemoryService(bram_controller_path)

historic_data_service = HistoricDataService(historic_data_directory)
bram = MemoryManagementResource(memory_service)
configuration = ConfigurationResource(configuration_service)
historic_configuration_list = HistoricConfigurationListResource(historic_configuration_service, inactive_historic_configuration_service)
historic_configuration = HistoricConfigurationResource(historic_configuration_service, configuration_cache, inactive_historic_configuration_service, historic_data_service)
historic_data_resource = HistoricDataResource(historic_data_service)
configuration_list = ConfigurationListResource(configuration_service)

api = application = falcon.API(middleware=[CORSInterceptor()])
api.add_route('/address/{address}', bram)

api.add_route('/configuration/all', configuration_list)
api.add_route('/configuration/{uuid_value}', configuration)
api.add_route('/configuration', configuration, suffix="add_configuration")

api.add_route('/historic-configuration/all', historic_configuration_list)
api.add_route('/historic-configuration/{uuid_value}', historic_configuration)
api.add_route('/historic-configuration/{uuid_value}/inactive', historic_configuration, suffix="move_to_inactive")
api.add_route('/historic-configuration', historic_configuration, suffix="new_configuration")

api.add_route('/historic-data/{uuid_value}/{chart_id}', historic_data_resource)

api.add_static_route('/', page_path, False, 'index.html')

historic_data_file_writer = HistoricDataFileWriter(historic_data_directory)
historic_data_gatherer_job = HistoricDataGathererJob(historic_data_gatherer_interval_seconds, configuration_cache, memory_service, historic_data_file_writer)
historic_data_gatherer_job.start()

historic_data_file_writer.start()
