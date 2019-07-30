import json

import falcon


class HistoricDataResource(object):
    def __init__(self, historic_data_service):
        self.historic_data_service = historic_data_service

    def on_get(self, req, resp, uuid_value, chart_id):
        data = self.historic_data_service.get_value_for_chart(uuid_value, chart_id)
        if data is None:
            resp.data = json.dumps({"error": 'cannot open folder with configurations'})
            resp.status = falcon.HTTP_500
            return
        resp.data = json.dumps(data)
        resp.status = falcon.HTTP_200
