int EN = 3 ;
int DIR = 10 ;
int STEP = 11 ;

void setup(){
pinMode(EN,OUTPUT);
pinMode(DIR,OUTPUT);
pinMode(STEP,OUTPUT);

digitalWrite(EN,HIGH);
digitalWrite(DIR,HIGH);
}

void loop(){
digitalWrite(EN,LOW);

for (int i=1;i<1000;i++){
digitalWrite(STEP,HIGH);
delay(1);
digitalWrite(STEP,LOW);
delay(1);
}
}



