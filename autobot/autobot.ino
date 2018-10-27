#include <NewPing.h>
NewPing sensor1(6, 7, 5000000);
#define FWD 12
#define BKD 11
#define SPEED 10
#define LEFT 8
#define RIGHT 9
const int pingPin = 7;
const int trig = 6;
int comp = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(FWD, OUTPUT);
  pinMode(BKD, OUTPUT);
  pinMode(SPEED, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  digitalWrite(SPEED, HIGH);
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  digitalWrite(FWD, HIGH);
  digitalWrite(RIGHT, LOW);
    digitalWrite(LEFT, LOW);

  comp = 0;
  while (sensor1.ping_cm() > 10) {
    delay(50);
  }
  
  digitalWrite(FWD,LOW);
  Serial.println("Cond 1 met");
  
  
  digitalWrite(LEFT, HIGH);
  for (int i = 0; i <= 18; i++) {
    digitalWrite(FWD, HIGH);
    Serial.println("IN loop 1");
    delay(500);
    digitalWrite(FWD, LOW);
    delay(500);
    if (sensor1.ping_cm() > 10) {
      comp = 1;
      digitalWrite(LEFT, LOW);
      Serial.println("cond 2 met");
      break;
    }
  }
  if ( comp == 0) {
    for (int i = 0; i <= 18; i++) {
      digitalWrite(BKD, HIGH);

      delay(500);
      digitalWrite(BKD, LOW);
     
    }
    digitalWrite(LEFT, LOW);
    digitalWrite(RIGHT, HIGH);
    for (int i = 0; i <= 18; i++) {
      digitalWrite(FWD, HIGH);

      delay(500);
      digitalWrite(FWD, LOW);
      delay(500);

      if (sensor1.ping_cm() > 10) {
              Serial.println("cond 3 met");

        break;
      }
    }
  }
  digitalWrite(FWD, LOW);
}


