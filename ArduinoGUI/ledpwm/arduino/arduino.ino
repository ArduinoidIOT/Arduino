/***********************************************************
File name: 05_serial.ino
Description: If you send a character ‘1’ or ‘0’ on the 
             serial monitor, the status of LED will be lit 
             or gone out.
Website: www.quadstore.in
***********************************************************/

int ledpin=11;           //definition digital 11 pins as pin to control the LED

void setup()
{
  Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps
  pinMode(ledpin,OUTPUT);//Set digital 11 port mode, the OUTPUT for the output
}
void loop()
{
    char recieveVal;                  // Defined receive data
   
    if(Serial.available() > 0)       //Receive serial data
    {        
        recieveVal = Serial.read();
        //recieveVal.trim();
        //Serial.println(recieveVal);
        //analogWrite(ledpin,51*recieveVal.toInt());
        if (recieveVal == '0'){
          analogWrite(ledpin,0);
        }
        else if (recieveVal == '1'){
          analogWrite(ledpin,51);
        }
        else if (recieveVal == '2'){
          analogWrite(ledpin,102);
        }
        else if (recieveVal == '3'){
          analogWrite(ledpin,153);
        }
        else if (recieveVal == '4'){
          analogWrite(ledpin,204);
        }
        else if (recieveVal == '5'){
          analogWrite(ledpin,255);
        }
     }
  //delay(50);                          //delay 50ms
}
