/***********************************************************
Author:Rohan Rao (rohroexperiment@gmail.com)
File name: serial.ino
Description: If you send ‘ON’ or ‘OFF’ to the 
             serial monitor, the status of LED will be  what
sent (ON or OFF).
***********************************************************/

int ledpin=13;           //Use pin 13 for LED

void setup()
{
  Serial.begin(9600);   // open serial port, set data rate to 9600 bps
  pinMode(ledpin,OUTPUT);//
}
void loop()
{
                      // Defined receive data
    if(Serial.available() > 0)       //Receive serial data
    {        
      //Serial.println("Recieved");
       String receiveVal = Serial.readString();  //Save the serial data received 
       Serial.println(receiveVal);
       receiveVal.trim();//remove trailing chars
       if(String(receiveVal)  == String("ON") )          //Receive data is ON, switch on  LED     
       { 
           digitalWrite(ledpin,HIGH); //Switch on LED
           Serial.println("LED:ON"); //send data to the serial monitor
       }
       if(String(receiveVal)  == String("OFF"))          //Received data is OFF, switch off LED 
       { 
           digitalWrite(ledpin,LOW);  //Switch off LED            
           Serial.println("LED:OFF");//send data to the serial monitor
      } 
    }
  delay(50);                          //delay 50ms
}

