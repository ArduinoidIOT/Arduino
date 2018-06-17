int BuzzerPin = 10;
int BuzzerPin2 = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(BuzzerPin,OUTPUT);//set output mode
  pinMode(BuzzerPin2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BuzzerPin,HIGH);//Buzzer 1 high
  digitalWrite(BuzzerPin2,LOW);//Buzzer 2 LOW
  delayMicroseconds(200); //delay .2 ms
  digitalWrite(BuzzerPin,LOW);//Buzzer 1 low
  
  digitalWrite(BuzzerPin2,HIGH);//Buzzer 2 high
  delayMicroseconds(200);//delay .2 ms
}
