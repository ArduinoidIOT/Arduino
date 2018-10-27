
#define DELAY 1666
void setup() {
  // put your setup code here, to run once:
  pinMode(8,OUTPUT);  
    pinMode(9,OUTPUT); 
    Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    delayMicroseconds(DELAY);
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    delayMicroseconds(DELAY);

}
