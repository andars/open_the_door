#!/usr/bin/env python
import SimpleHTTPServer
import SocketServer

import serial

ser = serial.Serial('/dev/ttyUSB1', 9600)

class MyRequestHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/open_door':
            ser.write('o')             
            self.send_response(200)
        elif self.path == '/close_door':
            ser.write('c')
            self.send_response(200)
        else:
            return SimpleHTTPServer.SimpleHTTPRequestHandler.do_GET(self)

handler = MyRequestHandler
server = SocketServer.TCPServer(('0.0.0.0', 8080), handler)

server.serve_forever()
