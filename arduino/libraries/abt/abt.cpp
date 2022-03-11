#include <abt.h>

int EN[3] = {X_ENABLE,Y_ENABLE,Z_ENABLE} ;
int DIR[3] = {X_DIR,Y_DIR,Z_DIR} ;
int STEP[3] = {X_STEP,Y_STEP,Z_STEP} ;

abt::abt(){
  // initialise led
  pinMode(LED_BUILTIN, OUTPUT) ;
  digitalWrite(LED_BUILTIN, LOW);

  // initialise linear actuator
  for (int i=0; i<3; i++){
    pinMode(EN[i],OUTPUT) ;
    pinMode(DIR[i],OUTPUT) ;
    pinMode(STEP[i],OUTPUT) ;
    digitalWrite(EN[i],HIGH) ;
    digitalWrite(DIR[i],HIGH) ;
  }

  // default parameters
  step = 1600;
  spd = 1000 ;
}

void abt::blink(int i){
  for(int j=0; j<i; j++){
  digitalWrite(LED_BUILTIN,HIGH) ;
  delay(100) ;
  digitalWrite(LED_BUILTIN,LOW) ;
  delay(100) ;
  }
}

void abt::spin(){

  digitalWrite(EN[motorNum],LOW) ;
  digitalWrite(DIR[motorNum], dir) ;

  for(int i=0; i<step; i++){
    digitalWrite(STEP[motorNum],HIGH) ;
    delayMicroseconds(spd) ;
    digitalWrite(STEP[motorNum],LOW) ;
    delayMicroseconds(spd) ;
  }
  digitalWrite(EN[motorNum], HIGH) ;
}

void abt::receive() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
//  char startMarker = '<';
  char endMarker = '\r';
  char rc;

  const byte numChars = 8;

  newData = false;

  while (Serial1.available() > 0 && newData == false) {
    rc = Serial1.read();
//    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
           ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
//    }

//    else if (rc == startMarker) {
//      recvInProgress = true;
//    }
  }
  
}
