#define MAXANIMATIONS 6

int data = 5;
int clock = 3;
int latch = 4;
int brightness = 200;
int animation = 1;
//Used for single LED manipulation
int ledState = 0;
const int ON = HIGH;
const int OFF = LOW;
byte pattern[] =
{
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010
};
byte pattern2[] { 129,66,36,24,36,66};
byte pattern3[] {B10000000,B00100000,B00001000,B00000010,B00000001,B00000100,B00010000,B01000000};
/*
   setup() - this function runs once when you turn your Arduino on
   We set the three control pins to outputs
*/

void setup()
{
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(0,nextAnimation,FALLING);
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  Serial.begin(9600);

}
void nextAnimation () {
  if (digitalRead(2) == LOW) {
    delayMicroseconds(10000);
    if (digitalRead(2) == LOW) {
      if (animation == MAXANIMATIONS) animation = 1;
      else animation++;   
    } 
    while (digitalRead(2)== LOW);
  }
}
  /*
     loop() - this function will start after setup finishes and then repeat
     we set which LEDs we want on then call a routine which sends the states to the 74HC595
  */
  void loop()                     // run over and over again
  {
       

    
    if (animation == 1) animation1();
    else if (animation == 2) animation2();
    else if(animation == 3) animation3();
    else if(animation ==4) animation4();
    else if (animation == 5) animation5();
    else if (animation == 6) animation6();
  }
void animation1 () {
    
    updateLEDs(0x55);
    delay(1000);
    updateLEDs(B10101010);
    delay(1000);

  }
void animation2 () {

    for (int i = 0; i < sizeof(pattern); i++) {
      updateLEDs(pattern[i]);
      delay(250);

    }
  }
  void animation3() {

    randomSeed(analogRead(A1));
    updateLEDs(random(255));
    delay(1000);

  }
  void animation4() {
    updateLEDs(0xff);
    delay(100);
    updateLEDs(0);
    delay(100);
  }
  void animation5() {
    for(int i =0;i < sizeof(pattern2);i++) {
      updateLEDs(pattern2[i]);
      delay(250);  
    }  
  }
  void animation6() {
    for(int i =0;i < sizeof(pattern3);i++) {
      updateLEDs(pattern3[i]);
      delay(250);  
    }  
  }
  /*
     updateLEDs() - sends the LED states set in ledStates to the 74HC595
     sequence
  */
  void updateLEDs(int value) {
    //digitalWrite(latch, LOW);     //Pulls the chips latch low
    //shiftOut(data, clock, LSBFIRST, value); //Shifts out the 8 bits to the shift register
    //digitalWrite(latch, HIGH);   //Pulls the latch high displaying the data
     digitalWrite(latch, LOW);    //Pulls the chips latch low
  for(int i = 0; i < 8; i++){  //Will repeat 8 times (once for each bit)
  int bit = value & B10000000; //We use a "bitmask" to select only the eighth 
                               //bit in our number (the one we are addressing this time through
  value = value << 1;          //we move our number up one bit value so next time bit 7 will be
                               //bit 8 and we will do our math on it
  if(bit == 128){digitalWrite(data, HIGH);} //if bit 8 is set then set our data pin high
  else{digitalWrite(data, LOW);} 
  //if bit 8 is unset then set the data pin low
  digitalWrite(clock, HIGH);                //the next three lines pulse the clock pin
  delay(1);
  digitalWrite(clock, LOW);
  }
  digitalWrite(latch, HIGH); 
  }

