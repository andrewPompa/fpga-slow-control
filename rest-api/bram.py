import falcon

from bram_resource import BramResource

api = application = falcon.API()

bram = BramResource()
api.add_route('/address/{address}', bram)
