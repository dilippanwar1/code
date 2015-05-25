#!/bin/python

from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler

url2Handlers = {}


# HTTP request handler.
class RequestHandler(BaseHTTPRequestHandler):

  def do_GET(self):
    self._writeheaders()
    func = url2Handlers.get(self.path, None)
    if func:
      self.wfile.write(func(self.request))
    else:
      self.wfile.write('No handler')

  def _writeheaders(self):
    self.send_response(200)
    self.send_header('Content-type', 'text/html')
    self.end_headers()


# Register a handler for given url.
def Register(url):
  def decorator(func):
    url2Handlers[url] = func
    def func_being_called(*args, **kwargs):
      return func(args, kwargs)
    return func_being_called
  return decorator


# Start server infinitely.
def StartServer(port):
  srvr = HTTPServer(('', port), RequestHandler)
  srvr.serve_forever()


#
# Above code can be think of as web framework code; following code
# can be think of as application code.
#
@Register('/hello')
def HelloHandler(request):
  print request
  return 'Hello'


@Register('/greeting')
def GreetingHandler(request):
  return 'Greeting'


StartServer(8000)
