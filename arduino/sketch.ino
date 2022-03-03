void setup() {
  // initialize the serial port:
  Serial1.begin(9600);

  // pinout
  pinMode(3,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  digitalWrite(3,HIGH);
  digitalWrite(10,HIGH);

  pinMode(LED_BUILTIN, OUTPUT) ;

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  //
  if (Serial1.available() > 0){
    char cmd = Serial1.read() ;
    if (cmd == '1'){
      digitalWrite(LED_BUILTIN, HIGH) ;
      digitalWrite(3, LOW) ;
      digitalWrite(10, HIGH) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(11,HIGH) ;
        delayMicroseconds(100) ;
        digitalWrite(11,LOW) ;
        delayMicroseconds(100) ;
      }
      Serial1.println("Forward") ;
      digitalWrite(3, HIGH) ;
    }
    if (cmd == '2'){
      digitalWrite(LED_BUILTIN, LOW) ;
      digitalWrite(3, LOW) ;
      digitalWrite(10, LOW) ;

      for (int i = 0; i < 1000; i++){
        digitalWrite(11,HIGH) ;
        delayMicroseconds(100) ;
        digitalWrite(11,LOW) ;
        delayMicroseconds(100) ;
      }
      Serial1.println("Backward") ;
      digitalWrite(3, HIGH) ;
    }
    if (cmd == 'a'){
	for (int i = 0; i < 5; i++){
	digitalWrite(LED_BUILTIN, HIGH) ;
	delay(100) ;
	digitalWrite(LED_BUILTIN, LOW) ;
	delay(100) ;
	}
    }

  }
}

