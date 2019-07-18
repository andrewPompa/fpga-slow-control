import falcon
import ConfigParser
from interceptors.cors_interceptor import CORSInterceptor
from resources.memory_management_resource import MemoryManagementResource
from resources.configuration_resource import ConfigurationResource
from resources.configuration_list_resource import ConfigurationListResource
from services.file_name_service import FileNameService

config = ConfigParser.ConfigParser()
config.read('server.cfg')
configuration_file_directory = config.get('CONFIGURATION', 'configuration_file_directory')
bram_controller_path = config.get('CONFIGURATION', 'bram_controller_path')
page_path = config.get('CONFIGURATION', 'page_path')

file_name_service = FileNameService(configuration_file_directory)

bram = MemoryManagementResource(bram_controller_path)
configuration = ConfigurationResource(file_name_service)
configuration_list = ConfigurationListResource(file_name_service)

api = application = falcon.API(middleware=[CORSInterceptor()])
api.add_route('/address/{address}', bram)
api.add_route('/configuration/all', configuration_list)
api.add_route('/configuration/{uuid_value}', configuration)
api.add_route('/configuration', configuration, suffix="add_configuration")
api.add_static_route('/', page_path, False, 'index.html')
