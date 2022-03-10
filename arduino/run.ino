#include <ADIS16405.h>
#include <SPI.h>
#include <abt.h>

// pin definition
#define X_ENABLE  3
#define X_DIR     10
#define X_STEP    11
#define Y_ENABLE  8
#define Y_DIR     2
#define Y_STEP    9
#define Z_ENABLE  6
#define Z_DIR     4
#define Z_STEP    12

#define IMU_CS    5
#define IMU_RST   7

int EN[3] = {X_ENABLE,Y_ENABLE,Z_ENABLE} ;
int DIR[3] = {X_DIR,Y_DIR,Z_DIR} ;
int STEP[3] = {X_STEP,Y_STEP,Z_STEP} ;

int spd = 1000;

ADIS16405 iSensor(IMU_CS) ;
abt abt ;

void blink(int i){
  for(int j=0; j<i; j++){
  digitalWrite(LED_BUILTIN, HIGH) ;
  delay(100) ;
  digitalWrite(LED_BUILTIN, LOW) ;
  delay(100) ;
  }
}

void setup() {
  // initialise led
  pinMode(LED_BUILTIN, OUTPUT) ;
  digitalWrite(LED_BUILTIN, LOW);

  // initialise serial port:
  Serial1.begin(115200);

  // initialise linear actuator
  for (int i=0; i<3; i++){
    pinMode(EN[i],OUTPUT) ;
    pinMode(DIR[i],OUTPUT) ;
    pinMode(STEP[i],OUTPUT) ;
    digitalWrite(EN[i],HIGH) ;
    digitalWrite(DIR[i],HIGH) ;
  }

  // initialise IMU
  SPI.setDataMode(SPI_MODE3) ;
  pinMode(IMU_RST, OUTPUT) ;
  digitalWrite(IMU_RST, LOW) ; 
  delay(100) ;
  digitalWrite(IMU_RST, HIGH) ;
  delay(100) ;
  iSensor.factory_reset() ;
  delay(100) ;
  iSensor.sens_avg() ;
  delay(100) ;
  iSensor.write(0x20, 0x1ffb) ;
  delay(100) ;
  iSensor.write(0x22, 0x1FFE) ;
  delay(100) ;
//  iSensor.gyro_prec_null() ;
 
}

void loop() {
  // linear actuator
  if (Serial1.available() > 0){
    char cmd = Serial1.read() ;
    if (cmd == '1'){
      abt.spin(X_ENABLE,X_DIR,X_STEP,1,1000,1000);
    }
    if (cmd == '2'){
      abt.spin(X_ENABLE,X_DIR,X_STEP,0,1000,1000);
    }
    if (cmd == '3'){
      abt.spin(Y_ENABLE,Y_DIR,Y_STEP,1,1000,1000);
    }
    if (cmd == '4'){
      abt.spin(Y_ENABLE,Y_DIR,Y_STEP,0,1000,1000);
    }
    if (cmd == '5'){
      abt.spin(Z_ENABLE,Z_DIR,Z_STEP,1,1000,1000);
    }
    if (cmd == '6'){
      abt.spin(Z_ENABLE,Z_DIR,Z_STEP,0,1000,1000);
    }

    if (cmd == 'a'){
      abt.blink(3);
    }
    
    if (cmd == 'q'){
      iSensor.burst_read() ;
      for (int i = 0; i < 12; i++){
        Serial1.print(iSensor.sensor[i], 3) ;
        Serial1.print(",") ;
      }
      Serial1.println();
    }
  }

}



