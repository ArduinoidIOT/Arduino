byte Pin0 = 2;//definition digital 8 pins as pin to control the IN1 (ULN24L01)
byte Pin1 = 3;//definition digital 9 pins as pin to control the IN2 (ULN24L01)
byte Pin2 = 4;//definition digital 10 pins as pin to control the IN3 (ULN24L01)
byte Pin3 = 5;//definition digital 11 pins as pin to control the IN4 (ULN24L01)
#include <Servo.h>
Servo srv0;
int _step = 512;
byte _speed = 1;
byte echo = 7;
byte trig = 6;
void setup()
{
  pinMode(Pin0, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  srv0.attach(8);
  srv0.write(90);
  delay(100);

  Serial.begin(9600);
}
int num;
void loop()
{
  //Stepper motor speed = 15 fast (note:speed from 1 to 15)
  while (ping(echo) > 15) {

    Step(8);//Stepper motor forward 512 steps ---- 360 angle
  }

  for ( num = 0; num <= 180; num++)
  {
    srv0.write(num);//back to 'num' degrees(0 to 180)
    delay(30);//control servo speed
    if (ping(echo) > 15) {
      break;
    }

  }
  
}
void Step(int _step)//Stepper motor rotation
{
  if (_step >= 0) { // Stepper motor forward
    for (int i = 0; i < _step; i++) {
      setStep(0, 0, 0, 1);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 1);
      delay(_speed);
    }
  }
}
void setStep(int a, int b, int c, int d)
{
  digitalWrite(Pin0, a);
  digitalWrite(Pin1, b);
  digitalWrite(Pin2, c);
  digitalWrite(Pin3, d);
}
int ping(int pingPin)
{
  long duration;
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance

  return duration / 29 / 2 ;
}


