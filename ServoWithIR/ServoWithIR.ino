/*
Author:Rohan Rao (rohroexperiment@gmail.com)
File name: ServoWithIR.ino
Description:
Control a servo using IR remote
 */
#include <Servo.h>
#include <IRremote.h>

int RECV_PIN = 5;//The reciever input

IRrecv irrecv(RECV_PIN);
Servo servo;
decode_results results;

void setup()
{
  Serial.begin(9600);//Set baud rate to 9600
  irrecv.enableIRIn(); // Start the receiver
  servo.attach(9);//Attach Servo to pin 9
  servo.write(90);//Set servo direction to 90
}
unsigned long recvd = 0;//Recieved value
long lastval = 0;
void loop() {
  if (irrecv.decode(&results)) {
    if(results.value == 0xE318261B){//  key '1'  pressed
      recvd *= 10;
      recvd += 1;
      Serial.println(1);
    }
    else if(results.value == 0x511DBB){ // key '2' pressed
      recvd *= 10;
      recvd += 2;
      Serial.println(2);
    }
    else if(results.value == 0xEE886D7F){// key '3' pressed
      recvd *= 10;
      recvd += 3;
      Serial.println(3);
    }
    else if(results.value == 0x52A3D41F){// key '4' pressed
      recvd *= 10;
      recvd += 4;
      Serial.println(4);
    }
    else if(results.value == 0xD7E84B1B){// key '5' pressed
      recvd *= 10;
      recvd += 5;
      Serial.println(5);
    }
    else if(results.value == 0x20FE4DBB){// key '6' pressed
      recvd *= 10;
      recvd += 6;
      Serial.println(6);
    }
    else if(results.value == 0xF076C13B){// key '7' pressed
      recvd *= 10;
      recvd += 7;
      Serial.println(7);
    }
    else if(results.value == 0xA3C8EDDB){// key '8' pressed
      recvd *= 10;
      recvd += 8;
      Serial.println(8);
    }
    else if(results.value == 0xE5CFBD7F){// key '9' pressed
      recvd *= 10;
      recvd += 9;
      Serial.println(9);
    }
    else if(results.value == 0x97483BFB){// key '0' pressed
      recvd *= 10;
      Serial.println(0);
      recvd += 0;
    }
    else if (results.value == 0x488F3CBB){// key 'OK' pressed
      Serial.print("Angle:");
      Serial.println(recvd % 181);
      servo.write(recvd % 181);
      recvd = 0;
    }
    
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value
    while (digitalRead(5));

  }
  delay(100);
  
}
