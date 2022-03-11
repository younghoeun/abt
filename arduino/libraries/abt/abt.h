#ifndef abt_h
#define abt_h
#include <Arduino.h>

// class definition
class abt{

public:

  abt();


  // blink led
  void blink(int number);
  // linear actuator
  void spin(int enablePIN, int dirPIN, int stepPIN, bool dir, int spd, int step);
  // command receiver

  char receivedChars[32] ;
  boolean newData ;
  void receive() ;

private:

};

#endif
