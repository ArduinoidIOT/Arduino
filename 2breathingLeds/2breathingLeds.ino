/***********************************************************
File name: 2breathingleds.ino
Description: 
	PWM controls 2 leds simultaenously, with 1 led getting brighter and the other led getting dimmer at the same time.
***********************************************************/
#define STEPSIZE 1
int ledpin=11;//definition digital 11 pins as pin to control the LED
int ledpin2 =10;//definition digital 12 pins as pin to control the LED
const int LIMIT = 100;//sets limit to 100
void setup ()
{
  pinMode(ledpin,OUTPUT);//Set digital 11 port mode, the OUTPUT for the output
  pinMode(ledpin2,OUTPUT);//Set digital 12 port mode, the OUTPUT for the output
  digitalWrite(ledpin,LOW);
  analogWrite(ledpin2,LIMIT);
}
void loop()
{
   for (int a=0; a<=LIMIT;a+=STEPSIZE)  //Loop, PWM control of LED brightness increase
   {
     analogWrite(ledpin,a);//PWM output value a(0~LIMIT)
     analogWrite(ledpin2,LIMIT-a);//PWM output value LIMIT-a (LIMIT~0)
     delay(50);                //The duration of the current brightness level. 50ms           
   }
   delay(1000);   //1s delay
   for (int a=LIMIT; a>=0;a-=STEPSIZE)  //Loop, PWM control of LED brightness Reduced
   {
     analogWrite(ledpin,a);//PWM output value a (LIMIT~0)
     analogWrite(ledpin2,LIMIT-a);//PWM output value LIMIT-a (0~LIMIT)
     delay(50);                //The duration of the current brightness level. 50ms 
   }
   delay(100);                //100ms delay
}
