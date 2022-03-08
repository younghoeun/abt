#include <ADIS16405.h>
#include <SPI.h>

// pin definition
#define X_ENABLE  3
#define X_DIR     10
#define X_STEP    11
#define Y_ENABLE  8
#define Y_DIR     2
#define Y_STEP    9
#define IMU_CS    5
#define IMU_RST   7

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
  // led
  pinMode(LED_BUILTIN, OUTPUT) ;
  digitalWrite(LED_BUILTIN, LOW);

  // initialize serial port:
  Serial1.begin(9600);
  Serial.begin(9600) ;

  // linear actuator
  pinMode(X_ENABLE,OUTPUT);
  pinMode(X_DIR,OUTPUT);
  pinMode(X_STEP,OUTPUT);

  pinMode(Y_ENABLE,OUTPUT);
  pinMode(Y_DIR,OUTPUT);
  pinMode(Y_STEP,OUTPUT);

  digitalWrite(X_ENABLE,HIGH);
  digitalWrite(X_DIR,HIGH);
  digitalWrite(Y_ENABLE,HIGH);
  digitalWrite(Y_DIR,HIGH);
  blink(1) ;

  // IMU
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

void loop() {
  // linear actuator
  if (Serial1.available() > 0){
    char cmd = Serial1.read() ;
    if (cmd == '1'){
      digitalWrite(LED_BUILTIN, HIGH) ;
      digitalWrite(X_ENABLE, LOW) ;
      digitalWrite(X_DIR, HIGH) ;

      digitalWrite(Y_ENABLE, LOW) ;
      digitalWrite(Y_DIR, HIGH) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(X_STEP,HIGH) ;
        digitalWrite(Y_STEP,HIGH) ;
        delayMicroseconds(100) ;
        digitalWrite(X_STEP,LOW) ;
        digitalWrite(Y_STEP,LOW) ;
        delayMicroseconds(100) ;
      }
      Serial1.println("Forward") ;
      digitalWrite(X_ENABLE, HIGH) ;
      digitalWrite(Y_ENABLE, HIGH) ;
    }
    if (cmd == '2'){
      digitalWrite(LED_BUILTIN, LOW) ;
      digitalWrite(X_ENABLE, LOW) ;
      digitalWrite(X_DIR, LOW) ;

      digitalWrite(Y_ENABLE, LOW) ;
      digitalWrite(Y_DIR, LOW) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(X_STEP,HIGH) ;
        digitalWrite(Y_STEP,HIGH) ;
        delayMicroseconds(100) ;
        digitalWrite(X_STEP,LOW) ;
        digitalWrite(Y_STEP,LOW) ;
        delayMicroseconds(100) ;
      }
      Serial1.println("Backward") ;
      digitalWrite(X_ENABLE, HIGH) ;
      digitalWrite(Y_ENABLE, HIGH) ;
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
        Serial1.print(iSensor.sensor[i], 6) ;
        Serial1.print(" ") ;
      }
      Serial1.println();
    }
  }

  iSensor.burst_read() ;
    for (int i = 0; i < 12; i++){
      Serial.print(iSensor.sensor[i], 6) ;
      Serial.print(" ") ;
    }
  Serial.println();
  delay(100) ;

}



