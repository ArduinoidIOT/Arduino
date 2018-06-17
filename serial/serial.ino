/***********************************************************
File name: serial.ino
Description: If you send a character ‘ON’ or ‘OFF’ on the 
             serial monitor, the status of LED will be lit 
             or gone out.
***********************************************************/

int ledpin=11;           //definition digital 11 pins as pin to control the LED

void setup()
{
  Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps
  pinMode(ledpin,OUTPUT);//Set digital 11 port mode, the OUTPUT for the output
}
void loop()
{
                      // Defined receive data
    if(Serial.available() > 0)       //Receive serial data
    {        
      Serial.println("Recieved");
       String receiveVal = Serial.readString();  //Save the serial data received 
       Serial.println(receiveVal);
       receiveVal.trim();//remove trailing chars
       if(String(receiveVal)  == String("ON") )          //Receive data is ON, lit LED lights    
       { 
           digitalWrite(ledpin,HIGH); //print out the value of the LED       
           Serial.println("LED:ON"); //send data to the serial monitor
       }
       if(String(receiveVal)  == String("OFF"))          //Receive data is OFF, off LED lights
       { 
           digitalWrite(ledpin,LOW);  //print out the value of the LED                
           Serial.println("LED:OFF");//send data to the serial monitor
      } 
    }
  delay(50);                          //delay 50ms
}

