int led = 10;
int incomingByte = 0; 

void setup() {
  pinMode(led, OUTPUT);
//  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
//  int sensorValue = analogRead(A0);
//  Serial.println(sensorValue);  
  digitalWrite(led, HIGH);   
  delay(100);                       
  digitalWrite(led, LOW);    
  delay(100);  
//  Serial.println("hello pi");
  Serial1.println("hello pi");
  delay(100);        // delay in between reads for stability
}

