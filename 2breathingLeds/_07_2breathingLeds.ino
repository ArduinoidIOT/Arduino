/***********************************************************
File name: 07_breathingLed.ino
Description: PWM control the LED gradually from dark to 
             brighter, then from brighter to dark
Website: www.quadstore.in
***********************************************************/
#define STEPSIZE 1
int ledpin=11;
int ledpin2 =10;//definition digital 11 pins as pin to control the LED
const int LIMIT = 100;
void setup ()
{
  pinMode(ledpin,OUTPUT);
  //Set digital 11 port mode, the OUTPUT for the output
  pinMode(ledpin2,OUTPUT);
  digitalWrite(ledpin,LOW);
  analogWrite(ledpin2,LIMIT);
}
void delay_noISR(int millisecs){
  
}
void loop()
{
   for (int a=0; a<=LIMIT;a+=STEPSIZE)  //Loop, PWM control of LED brightness increase
   {
     analogWrite(ledpin,a);
     analogWrite(ledpin2,LIMIT-a);//PWM output value a (0~255)
     delay(50);                //The duration of the current brightness level. 15ms           
   }
   delay(1000);   
   for (int a=LIMIT; a>=0;a-=STEPSIZE)  //Loop, PWM control of LED brightness Reduced
   {
     analogWrite(ledpin,a);
     analogWrite(ledpin2,LIMIT-a);//PWM output value a (255~0)
     delay(50);                //The duration of the current brightness level. 15ms 
   }
   delay(100);                //100ms delay
}
