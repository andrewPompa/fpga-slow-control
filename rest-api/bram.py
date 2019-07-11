import falcon
from falcon.http_status import HTTPStatus

from bram_resource import BramResource

page_path = 'path-to-page'


class HandleCORS(object):

    def process_request(self, req, resp):
        resp.set_header('Access-Control-Allow-Origin', '*')
        resp.set_header('Access-Control-Allow-Methods', 'GET,HEAD,POST,PATCH,OPTIONS')
        resp.set_header('Access-Control-Allow-Headers', 'content-type')
        resp.set_header('Access-Control-Max-Age', 1728000)  # 20 days
        if req.method == 'OPTIONS':
            raise HTTPStatus(falcon.HTTP_200, body='\n')


api = application = falcon.API(middleware=[HandleCORS()])

bram = BramResource()
api.add_route('/address/{address}', bram)
api.add_static_route('/', page_path, False, 'index.html')
