int BuzzerPin = 10;
int BuzzerPin2 = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(BuzzerPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BuzzerPin,HIGH);
  digitalWrite(BuzzerPin2,LOW);
  delayMicroseconds(200);
  digitalWrite(BuzzerPin,LOW);
  
  digitalWrite(BuzzerPin2,HIGH);
  delayMicroseconds(200);
}
