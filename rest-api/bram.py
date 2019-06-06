import falcon

from bram_resource import BramResource

api = application = falcon.API()

images = BramResource()
api.add_route('/address/{address}', images)
