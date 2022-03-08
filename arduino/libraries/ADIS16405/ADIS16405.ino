#include "ADIS16405.h"
#include <SPI.h>

#define CS5 10     //  IMU CHIP SELECT
#define RST 9     //  IMU RESET

ADIS16364 iSensor(CS5);

void setup () {
  Serial.begin(115200);
  Serial.setTimeout(10); 
  Serial.println("Serial ready");
  
  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  delay(100);
  digitalWrite(RST, HIGH);
  // Start serial
  delay(100);
  iSensor.factory_reset();
  delay(100);

  iSensor.sens_avg();
  delay(10);
  iSensor.write(0x20, 0x1ffb);
  delay(100);
  iSensor.write(0x22,0x1FFE);
  delay(100);
//  iSensor.gyro_prec_null();

  Serial.println("IMU ready");
}

void loop()
{
  long t = millis();

  SPI.setDataMode(SPI_MODE3);
  iSensor.burst_read();

  Serial.print(t);
  Serial.print(" ");
  
  for (int i = 7; i < 10; i++) {
    if (i < 10) {
      Serial.print(iSensor.sensor[i], 6);
      Serial.print(" ");
    }
  }
  Serial.println();

//  double field = sqrt(sq(iSensor.sensor[7]) + sq(iSensor.sensor[8]) + sq(iSensor.sensor[9]));
//  Serial.println(field);

  if(Serial.available() > 0){
    char cmd = Serial.read();
    if (cmd == 'q'){
      Serial.println("alignment");
      iSensor.write(0x34,0x0046);
      delay(100);
     }
     else if (cmd == 'w'){
      Serial.println("default");
      iSensor.write(0x34,0x0006);
      delay(100);
     }
  }
  
  delay(10);
}
