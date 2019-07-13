import falcon
import ConfigParser
from cors_interceptor import CORSInterceptor
from bram_resource import BramResource
from configuration_resource import ConfigurationResource

config = ConfigParser.ConfigParser()
config.read('server.cfg')
config_file_path = config.get('CONFIGURATION', 'file_path')
page_path = config.get('CONFIGURATION', 'page_path')

bram = BramResource()
configuration = ConfigurationResource(config_file_path)

api = application = falcon.API(middleware=[CORSInterceptor()])
api.add_route('/address/{address}', bram)
api.add_route('/configuration', configuration)
api.add_static_route('/', page_path, False, 'index.html')
