import serial
import time
import os

port = "/dev/ttyS0"

s = serial.Serial(port, 9600, timeout = 2)
s.close()
s.open()

print(s.is_open)

def clear():
    command = 'clear'
    os.system(command)

clear()

while True:
  cmd = input()
  clear()
  	
  s.write(cmd.encode("ascii"))
  while s.inWaiting() < 9:
    time.sleep(0.01)

  remaining = s.inWaiting()
  packet = s.read(remaining)
  print (packet.decode("ascii"))

s.close()

