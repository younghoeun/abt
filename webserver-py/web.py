
#!/usr/bin/env python3

import os
import time
import serial
from http.server import BaseHTTPRequestHandler, HTTPServer

host_name = '10.0.4.40'  # IP Address of Raspberry Pi
host_port = 8000

serial_port = serial.Serial('/dev/ttyS0', 9600, timeout = 0.1)

def forward():
    cmd = "1"
    serial_port.write(cmd.encode("ascii"))
    time.sleep(0.1)
    pck = serial_port.readline()
    print(pck.decode("ascii"))

def backward():
    cmd = "2"
    serial_port.write(cmd.encode("ascii"))
    time.sleep(0.1)
    pck = serial_port.readline()
    print(pck.decode("ascii"))

def getTemperature():
    temp = os.popen("vcgencmd measure_temp").read()
    return temp

class MyServer(BaseHTTPRequestHandler):

    def do_HEAD(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def _redirect(self, path):
        self.send_response(303)
        self.send_header('Content-type', 'text/html')
        self.send_header('Location', path)
        self.end_headers()

    def do_GET(self):
        html = '''
           <html>
           <body 
            style="width:960px; margin: 20px auto;">
           <h1>Air Bearing Table Cockpit</h1>
           <p>CPU temperature: {}</p>
           <form action="/" method="POST">
               Manual balance mode :
    	       <br>
               <input type="submit" name="submit" value="Forward"><br><br>
               <input type="submit" name="submit" value="Backward">
           </form>
           </body>
           </html>
        '''
        temp = getTemperature()

        self.do_HEAD()
        self.wfile.write(html.format(temp[5:]).encode("utf-8"))

    def do_POST(self):

        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode("utf-8")
        post_data = post_data.split("=")[1]

        if post_data == 'Forward':
            forward()
        else:
            backward()

#        print("moving {}".format(post_data))
        self._redirect('/')  # Redirect back to the root url


# # # # # Main # # # # #

if __name__ == '__main__':
    http_server = HTTPServer((host_name, host_port), MyServer)
    print("Server Starts - %s:%s" % (host_name, host_port))

    try:
        http_server.serve_forever()
    except KeyboardInterrupt:
        http_server.server_close()
