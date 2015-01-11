# A simple http server to experiment with interface.
#
# Esay and obvious fact:
# If server address is 127.0.0.1 or localhost, then only works on local machine.
# If server address is 0.0.0.0 or any public address on an interface, then
#    server can be accessed from outside world.

import sys
import BaseHTTPServer
from SimpleHTTPServer import SimpleHTTPRequestHandler

HandlerClass = SimpleHTTPRequestHandler
ServerClass = BaseHTTPServer.HTTPServer
Protocol = "HTTP/1.0"

port = 8990
# Change to 0.0.0.0, then server can be accessed from outside world, e.g.
# deyuan.me:8990
server_address = ('127.0.0.1', port)

HandlerClass.protocol_version = Protocol
httpd = ServerClass(server_address, HandlerClass)

sa = httpd.socket.getsockname()
print "Serving HTTP on", sa[0], "port", sa[1], "..."
httpd.serve_forever()
