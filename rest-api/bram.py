import falcon

from bram_resource import BramResource

page_path = 'path-to-page'
api = application = falcon.API()

bram = BramResource()
api.add_route('/address/{address}', bram)
api.add_static_route('/', page_path, False, 'index.html')
