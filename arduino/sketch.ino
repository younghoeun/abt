#include <ADIS16405.h>
#include <SPI.h>
#include <abt.h>

// pin definition
#define IMU_CS    5
#define IMU_RST   7

//int EN[3] = {X_ENABLE,Y_ENABLE,Z_ENABLE} ;
//int DIR[3] = {X_DIR,Y_DIR,Z_DIR} ;
//int STEP[3] = {X_STEP,Y_STEP,Z_STEP} ;

ADIS16405 iSensor(IMU_CS) ;
abt abt ;

void setup() {
  // initialise serial port:
  Serial1.begin(115200);

  // initialise led
//  pinMode(LED_BUILTIN, OUTPUT) ;
//  digitalWrite(LED_BUILTIN, LOW);

/*
  // initialise linear actuator
  for (int i=0; i<3; i++){
    pinMode(EN[i],OUTPUT) ;
    pinMode(DIR[i],OUTPUT) ;
    pinMode(STEP[i],OUTPUT) ;
    digitalWrite(EN[i],HIGH) ;
    digitalWrite(DIR[i],HIGH) ;
  }
*/

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

  abt.receive() ;

  if(abt.newData == true){
    if (abt.receivedChars[0] == 'x'){
      abt.motorNum = 0;
      if (abt.receivedChars[1] == '+'){
        abt.dir = true ;
        abt.spin();
      }
      if (abt.receivedChars[1] == '-'){
        abt.dir = false ;
        abt.spin();
      }
    }
    if (abt.receivedChars[0] == '+'){
      abt.spd = abt.spd - 100 ;
        if (abt.spd <= 0){
	  abt.spd = 50;
	}
    }
    if (abt.receivedChars[0] == '-'){
      abt.spd = abt.spd + 100 ;
    }
  
    if (abt.receivedChars[0] == 'a'){
      abt.blink(3);
    }

// transmit imu reading to pi
    if (abt.receivedChars[0] == 'q'){
      iSensor.burst_read() ;
      for (int i = 0; i < 12; i++){
        Serial1.print(iSensor.sensor[i], 3) ;
        Serial1.print(",") ;
      }
      Serial1.println();
    }

// telemetry
    if (abt.receivedChars[0] == 't'){
      Serial1.println("Motor Parameters") ;
      Serial1.print("Speed: ") ;
      Serial1.println(abt.spd) ;
      Serial1.print("Step: ") ;
      Serial1.println(abt.step) ;
    }

  }


}



