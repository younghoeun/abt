#include "abt.h"

abt::abt(){
  // initialise led
  pinMode(LED_BUILTIN, OUTPUT) ;
  digitalWrite(LED_BUILTIN, LOW);
}

void abt::blink(int i){
  for(int j=0; j<i; j++){
  digitalWrite(LED_BUILTIN,HIGH) ;
  delay(100) ;
  digitalWrite(LED_BUILTIN,LOW) ;
  delay(100) ;
  }
}

void abt::spin(int enablePIN, int dirPIN, int stepPIN, bool dir, int spd, int step){
  digitalWrite(enablePIN,LOW) ;
  digitalWrite(dirPIN, dir) ;

  for(int i=0; i<step; i++){
    digitalWrite(stepPIN,HIGH) ;
    delayMicroseconds(spd) ;
    digitalWrite(stepPIN,LOW) ;
    delayMicroseconds(spd) ;
  }
  digitalWrite(enablePIN, HIGH) ;
}

void abt::receive() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  const byte numChars = 32;
//  char receivedChars[numChars];

  newData = false;

  while (Serial1.available() > 0 && newData == false) {
    rc = Serial1.read();
    if (recvInProgress == true) {
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
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
  
}
