import falcon
import ConfigParser
from interceptors.cors_interceptor import CORSInterceptor
from resources.memory_management_resource import MemoryManagementResource
from resources.configuration_resource import ConfigurationResource
from resources.configuration_list_resource import ConfigurationListResource

config = ConfigParser.ConfigParser()
config.read('server.cfg')
configuration_file_directory = config.get('CONFIGURATION', 'configuration_file_directory')
bram_controller_path = config.get('CONFIGURATION', 'bram_controller_path')
page_path = config.get('CONFIGURATION', 'page_path')

bram = MemoryManagementResource(bram_controller_path)
configuration = ConfigurationResource(configuration_file_directory)
configuration_list = ConfigurationListResource(configuration_file_directory)

api = application = falcon.API(middleware=[CORSInterceptor()])
api.add_route('/address/{address}', bram)
api.add_route('/configuration/all', configuration_list)
api.add_route('/configuration/{uuid}', configuration)
api.add_static_route('/', page_path, False, 'index.html')
