#include "abt.h"

abt::abt(){

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
