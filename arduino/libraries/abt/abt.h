#ifndef abt_h
#define abt_h
#include <Arduino.h>

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

// class definition
class abt{

public:

  abt();

  // blink led
  void blink(int number);

  // linear actuator
  int motorNum ;
  boolean dir ;
  boolean enable ;
  int spd ;
  int step ;
  void spin();

  // command receiver
  char receivedChars[8] ;
  boolean newData ;
  void receive() ;

private:

};

#endif
