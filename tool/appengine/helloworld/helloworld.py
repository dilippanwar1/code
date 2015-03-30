# Download Google Appengine SDK and start dev using:
#   $ dev_appserver.py app.yaml
# Use appcfg.py to upload to GAE.

import webapp2

class MainPage(webapp2.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.write('Hello, World!')

app = webapp2.WSGIApplication([
  ('/', MainPage),
], debug=True)
