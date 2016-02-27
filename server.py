#!/usr/bin/env python
import SimpleHTTPServer
import SocketServer

import serial
import glob

def find_path():
    return glob.glob('/dev/ttyUSB*')[0]

ser = serial.Serial(find_path(), 9600)


def send_command(cmd):
    global ser
    for i in range(2):
        try:
            ser.write(cmd)
        except serial.SerialException as e:
            if i < 2:
                ser = serial.Serial(find_path(), 9600)
            else:
                return 404
        return 200

class MyRequestHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
    def do_GET(self):

        if self.path == '/open_door':
            self.send_response(send_command('a'))
        elif self.path == '/lock_door':
            self.send_response(send_command('c'))
        elif self.path == '/unlock_door':
            self.send_response(send_command('o'))
        else:
            return SimpleHTTPServer.SimpleHTTPRequestHandler.do_GET(self)

handler = MyRequestHandler
server = SocketServer.TCPServer(('0.0.0.0', 8080), handler)

server.serve_forever()
