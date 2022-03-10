#include <ADIS16405.h>
#include <SPI.h>

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

int spd = 1000;
int EN[3] = {3,8,6} ;
int DIR[3] = {10,2,4} ;
int STEP[3] = {11,9,12} ;

ADIS16405 iSensor(IMU_CS) ;

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
  blink(1) ;

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
 
  blink(2) ;

}

char cmd[10];

void loop() {
  // linear actuator
  if (Serial1.available() > 0){
    char cmd = Serial1.read() ;
    if (cmd == '1'){
      blink(1);
      digitalWrite(X_ENABLE, LOW) ;
      digitalWrite(X_DIR, HIGH) ;
      for (int i = 0; i < 1000; i++){
        digitalWrite(X_STEP,HIGH) ;
        delayMicroseconds(spd) ;
        digitalWrite(X_STEP,LOW) ;
        delayMicroseconds(spd) ;
      }
      digitalWrite(X_ENABLE, HIGH) ;
    }
    if (cmd == '2'){
      blink(1);
      digitalWrite(X_ENABLE, LOW) ;
      digitalWrite(X_DIR, LOW) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(X_STEP,HIGH) ;
        delayMicroseconds(spd) ;
        digitalWrite(X_STEP,LOW) ;
        delayMicroseconds(spd) ;
      }
      digitalWrite(X_ENABLE, HIGH) ;
    }
    if (cmd == '3'){
      blink(1);
      digitalWrite(Y_ENABLE, LOW) ;
      digitalWrite(Y_DIR, HIGH) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(Y_STEP,HIGH) ;
        delayMicroseconds(spd) ;
        digitalWrite(Y_STEP,LOW) ;
        delayMicroseconds(spd) ;
      }
      digitalWrite(Y_ENABLE, HIGH) ;
    }
    if (cmd == '4'){
      blink(1);
      digitalWrite(Y_ENABLE, LOW) ;
      digitalWrite(Y_DIR, LOW) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(Y_STEP,HIGH) ;
        delayMicroseconds(spd) ;
        digitalWrite(Y_STEP,LOW) ;
        delayMicroseconds(spd) ;
      }
      digitalWrite(Y_ENABLE, HIGH) ;
    }
    if (cmd == '5'){
      blink(1);
      digitalWrite(Z_ENABLE, LOW) ;
      digitalWrite(Z_DIR, HIGH) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(Z_STEP,HIGH) ;
        delayMicroseconds(spd) ;
        digitalWrite(Z_STEP,LOW) ;
        delayMicroseconds(spd) ;
      }
      digitalWrite(Z_ENABLE, HIGH) ;
    }
    if (cmd == '6'){
      blink(1);
      digitalWrite(Z_ENABLE, LOW) ;
      digitalWrite(Z_DIR, LOW) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(Z_STEP,HIGH) ;
        delayMicroseconds(spd) ;
        digitalWrite(Z_STEP,LOW) ;
        delayMicroseconds(spd) ;
      }
      digitalWrite(Z_ENABLE, HIGH) ;
    }

    if (cmd == 'a'){
	for (int i = 0; i < 5; i++){
	digitalWrite(LED_BUILTIN, HIGH) ;
	delay(100) ;
	digitalWrite(LED_BUILTIN, LOW) ;
	delay(100) ;
	}
    }
    if (cmd == 'z'){
	digitalWrite(X_STEP,HIGH) ;
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

  delay(1) ;

}



