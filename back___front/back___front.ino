//#define fwd 12
//#define bkd 11
#define SPEED 10
#define MAXDIST 7
int fwd =12;
int bkd = 11;
int trigPin = 6;
int pingPin = 7;
void setup() {
  // put your setup code here, to run once:
  pinMode(fwd,OUTPUT);
  pinMode(bkd,OUTPUT);
    pinMode(SPEED,OUTPUT);
  analogWrite(SPEED,255);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(fwd,HIGH);
  while(ping(pingPin,trigPin) > MAXDIST);
  digitalWrite(fwd,LOW);
  delay(500);
  digitalWrite(bkd,HIGH);
  delay(5000);
  digitalWrite(bkd,LOW);
  
}
int ping(int pingPin,int trigPin) 
{ 
   // establish variables for duration of the ping, 
   // and the distance result in inches and centimeters: 
   long duration, cm; 
   // The PING))) is triggered by a HIGH pulse of 2 or more microseconds. 
   // Give a short LOW pulse beforehand to ensure a clean HIGH pulse: 
   pinMode(trigPin, OUTPUT); 
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
   digitalWrite(trigPin, HIGH); 
   delayMicroseconds(10); 
   digitalWrite(trigPin, LOW); 

   pinMode(pingPin, INPUT); 
   duration = pulseIn(pingPin, HIGH); 

   // convert the time into a distance 
   
   return duration/58 ; 
}
void calibrate() {
int dist = ping(pingPin,trigPin);
digitalWrite(fwd,HIGH);
delay(1000);
digitalWrite(fwd,LOW);
int newdist = ping(pingPin,trigPin);
if (newdist > dist) {
 fwd=11;
 bkd=12 ; 
}
digitalWrite(bkd,HIGH);
delay(1000);
digitalWrite(bkd,LOW);
}
