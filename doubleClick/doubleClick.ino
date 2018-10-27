/***********************************************************
Author:Rohan Rao (rohroexperiment@gmail.com) 
 File name:doubleClick.ino
  Description: Using interrupts, every time you double-click one led toggles
and when you single-click the other led toggles
***********************************************************/

int ledpin = 11;//definition digital 11 pins as pin to control the LED
int ledpin2 = 12; //definition digital 12 pins as pin to control the LED
int btnpin = 2;           //Set the digital pin 2 to button interface
volatile int state = LOW; //LED 1 status
volatile int state2 = LOW;//Defined output status LED Interface
void setup()
{
  pinMode(ledpin, OUTPUT);//Set digital 11 port mode, the OUTPUT for the output
  pinMode(ledpin2, OUTPUT);//Set digital 12 port mode, the OUTPUT for the output
  attachInterrupt(0, stateChange, FALLING);//Monitoring Interrupt 0 (Digital PIN 2) cwhen it falls from HIGH to LOW
}

void loop()
{
  digitalWrite(ledpin, state);//Set LED 1 to state 1
  digitalWrite(ledpin2, state2);//Set LED 2 to state 2
}

void stateChange()                          //ISR
{
  cli(); // clear interrupts flag
  detachInterrupt(0);//Disable this interrupt
  int clicks = 0;
  
  if (detectClick() > 0) {//detect click
     clicks++;
  }  else {//re-enables this interrupt and exits
    sei();
    attachInterrupt(0, stateChange, FALLING);
    return;
  }

  blockForHigh();
	//detect second click
  for (int i = 0; i <= 100; i++) {
    if (detectClick() > 0) {
      clicks++;
      break;
    }
    delayMicroseconds(2000);//delays 2 ms
  }

  if (clicks == 1) {
    state = !state;//toggle led 1
  }else if (clicks == 2) {
    state2 = !state2;//toggle led 2
  }
  blockForHigh();
	//reenables interrupts
  sei();
  attachInterrupt(0, stateChange, FALLING);
}

//detect and confirm click
int detectClick() {
   if (digitalRead(btnpin) == LOW)           //Check if button pin is low
    {
      delayMicroseconds(10000);             //Delay 10ms for the elimination of key leading-edge jitter
      if (digitalRead(btnpin) == LOW)       //Confirm button is pressed
      {
        return 1;
      }
    }

    return 0;
}

//wait till button release
void blockForHigh() {
  while (digitalRead(btnpin) == LOW);
  delayMicroseconds(10000);//delay 10ms
  while (digitalRead(btnpin) == LOW);
  delayMicroseconds(10000);//delay 10ms
}

