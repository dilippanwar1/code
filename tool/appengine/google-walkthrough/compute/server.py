#!/usr/bin/python
from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer
from os import system
from urllib import unquote

import gcs

PORT_NUMBER = 8000

import re, string
pattern = re.compile('[\W_]+')

#This class takes in a url with a ?text= parameter and returns a WAV file
class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        if 'favicon' in self.path: return
        text = pattern.sub('', unquote(self.path.split("?text=")[1]))
        file_path = text + ".wav"

        system("espeak %s -w %s" % (text, file_path))
        self.send_header('Content-type','audio/wav')
        self.end_headers()
        # Send the html message

        file_contents = open(file_path).read()

        '''Write file contents to Cloud Storage'''
        '''YOUR CODE HERE'''
        gcs.write_to_storage(file_path)

        self.wfile.write(file_contents)
        system("rm -f %s.wav" % text)
        return
try:
    #Check if espeak is installed
    if system("espeak test -w test.wav") > 10:
        print 'Espeak is not installed. Please install espeak first and run this again.'
        exit()

    #Start the http server
    server = HTTPServer(('', PORT_NUMBER), Handler)
    print 'Started httpserver on port ' , PORT_NUMBER
    server.serve_forever()

except KeyboardInterrupt:
    print '^C received, shutting down the web server'
    server.socket.close()
