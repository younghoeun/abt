
#include <ADIS16405.h>
#include <SPI.h>
#include <abt.h>

// pin definition
#define IMU_CS    5
#define IMU_RST   7

ADIS16405 iSensor(IMU_CS) ;
abt abt ;

boolean flag ;
int step = 1600 ;
char motorNum[3] = "xyz" ;
char dir[2] = "-+" ;

void setup() {
  // initialise serial port:
  Serial1.begin(115200);

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

  Serial1.println("air bearing table cockpit") ;
}

void loop() {

  abt.receive() ;

  if(abt.newData == true){
    if (abt.receivedChars[0] == 'x'){
      abt.motorNum = 0;
    }
    if (abt.receivedChars[0] == 'y'){
      abt.motorNum = 1;
    }
    if (abt.receivedChars[0] == 'z'){
      abt.motorNum = 2;
    }
    { 
      if (abt.receivedChars[0] == '+'){
        abt.dir = true ;
      }
      if (abt.receivedChars[0] == '-'){
        abt.dir = false ;
      }
    }

    if (abt.receivedChars[0] == '1'){
      abt.spd = abt.spd - 100 ;
        if (abt.spd <= 0){
	  abt.spd = 50;
	}
    }
    if (abt.receivedChars[0] == 'q'){
      abt.spd = abt.spd + 100 ;
    }

// precision mode
    if (abt.receivedChars[0] == 'p'){
      step = 1 ;
    }
    
    if (abt.receivedChars[0] == 'n'){
      step = 16 ;
    }

// reset
    if (abt.receivedChars[0] == 'r'){
      abt.step = 160 ;
      abt.spd = 1000 ;
    }

    if (abt.receivedChars[0] == '2'){
      abt.step = abt.step + step ;
    }
    if (abt.receivedChars[0] == 'w'){
      abt.step = abt.step - step ;
        if (abt.spd <= 0){
	  abt.spd = step;
	}
    }
  
    if (abt.receivedChars[0] == 'a'){
      abt.blink(3);
    }

// transmit imu reading to pi
    if (abt.receivedChars[0] == 'o'){
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
      Serial1.print("Current motor: ") ;
      	            
      Serial1.println(motorNum[abt.motorNum]) ;
      Serial1.print("Direction: ") ;
      Serial1.println(dir[abt.dir]) ;
      Serial1.print("Speed: ") ;
      Serial1.println(abt.spd) ;
      Serial1.print("Step: ") ;
      Serial1.println(abt.step) ;
      Serial1.print("Status: ") ;
      Serial1.println(abt.enable) ;
      Serial1.print("flag: ") ;
      Serial1.println(flag) ;

    }

    if(abt.receivedChars[0] == 'g'){
      abt.spin() ;
      flag = true;
    }
    if(abt.receivedChars[0] == 's'){
      flag = false;
    }
  }
 
  
//  if (flag == true){
//    abt.spin();
//  }

//  if(abt.receivedChars[0] == 'd'){
//    abt.spd = 50 ;
//    abt.step = 10000 ;
//  
//      abt.dir = true ;
//      abt.spin() ;
//    Serial1.println("1") ;
//    abt.step = 20000 ;
//      abt.dir = false ;
//      abt.spin() ;
//    Serial1.println("2") ;
//      abt.dir = true ;
//      abt.spin() ;
//     Serial1.println("3") ;
// abt.step = 10000 ;
//      abt.dir = false ;
//      abt.spin() ;
//    Serial1.println("4") ;
//
//  }

}



