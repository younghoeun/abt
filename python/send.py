import serial
import io
import time

port = "/dev/ttyAMA0"

serialPort = serial.Serial(port, 9600, timeout = 1)

while True:
  cmd = input()
  print(cmd)
  serialPort.write(b'1')
  time.sleep(0.01)

serialPort.close()

