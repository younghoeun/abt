import serial

test_string = "Test serial port ...".encode("UTF-8")
port = "/dev/ttyS0"

try:
  serialPort = serial.Serial(port, 9600, timeout = 2)
  print ("Serial port", port, " ready for test :")
  bytes_sent = serialPort.write(test_string)
  print ("Sended", bytes_sent, "byte")
  loopback = serialPort.read(bytes_sent)
  if loopback == test_string:
    print ("Received ",len(loopback), "bytes. Port", port,"is OK ! \n")
    print (loopback.decode("ascii"))
  else:
    print ("Received incorrect data:", loopback, "on serial part", port, "loopback \n")
  serialPort.close()
except IOError:
  print ("Error on", port,"\n")
