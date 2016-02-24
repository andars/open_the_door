#!/usr/bin/env python
import SimpleHTTPServer
import SocketServer

import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)

class MyRequestHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/open_door':
            ser.write('o')             
        return SimpleHTTPServer.SimpleHTTPRequestHandler.do_GET(self)

handler = MyRequestHandler
server = SocketServer.TCPServer(('0.0.0.0', 8080), handler)

server.serve_forever()
