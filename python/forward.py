import serial
import time
import os

port = "/dev/ttyS0"

s = serial.Serial(port, 9600, timeout = 1)

cmd = "1"
s.write(cmd.encode("ascii"))

pck = s.read(8)
print(pck.decode("ascii"))

print("100")

s.close()

