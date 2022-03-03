import serial
import time
import os
import keyboard


port = "/dev/ttyS0"

s = serial.Serial(port, 9600, timeout = 1)

while True:
  print(keyboard.is_pressed("1"))
  time.sleep(0.1)
