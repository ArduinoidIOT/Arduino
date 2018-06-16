void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
}
volatile int state = LOW;
void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == HIGH){
    delay(10);
    if (digitalRead(2) == HIGH){}
        while(digitalRead(2)==HIGH){};//Wait for key interfaces to high
        delay(10);                      //delay 10ms for the elimination of key trailing-edge jitter
        while(digitalRead(2)==HIGH){};
        state = !state;
        digitalWrite(13,state);
    }
    
}
