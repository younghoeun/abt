import serial
from time import sleep

ser = serial.Serial(
        port='/dev/ttyS0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

while True:
    print("recieving via serial...")
#    received_data = ser.read()              #read serial port
#    sleep(0.03)
#    data_left = ser.inWaiting()             #check for remaining byte
#    received_data += ser.read(data_left)

    received = ser.readline().decode('utf-8').rstrip()
    print(received)
#    ser.write(received_data)  
