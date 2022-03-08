int X_ENABLE = 3;
int X_DIR = 10;
int X_STEP = 11;
int Y_ENABLE = 8;
int Y_DIR = 2;
int Y_STEP = 9;


void setup() {
  // initialize the serial port:
  Serial1.begin(9600);

  // pinout
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

  pinMode(LED_BUILTIN, OUTPUT) ;

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  //
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

  }
}

