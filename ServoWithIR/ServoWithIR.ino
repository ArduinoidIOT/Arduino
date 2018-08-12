/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <Servo.h>
#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
Servo servo;
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  servo.attach(9);
  servo.write(90);
}
unsigned long int recvd = 0;
void loop() {
  if (irrecv.decode(&results)) {
    if(results.value == 0xE318261B){//52A3D41F
      recvd *= 10;
      recvd += 1;
      Serial.println(1);
    }
    else if(results.value == 0x511DBB){
      recvd *= 10;
      recvd += 2;
      Serial.println(2);
    }
    else if(results.value == 0xEE886D7F){
      recvd *= 10;
      recvd += 3;
      Serial.println(3);
    }
    else if(results.value == 0x52A3D41F){
      recvd *= 10;
      recvd += 4;
      Serial.println(4);
    }
    else if(results.value == 0xD7E84B1B){
      recvd *= 10;
      recvd += 5;
      Serial.println(5);
    }
    else if(results.value == 0x20FE4DBB){
      recvd *= 10;
      recvd += 6;
      Serial.println(6);
    }
    else if(results.value == 0xF076C13B){
      recvd *= 10;
      recvd += 7;
      Serial.println(7);
    }
    else if(results.value == 0xA3C8EDDB){
      recvd *= 10;
      recvd += 8;
      Serial.println(8);
    }
    else if(results.value == 0xE5CFBD7F){
      recvd *= 10;
      recvd += 9;
      Serial.println(9);
    }
    else if(results.value == 0x97483BFB){
      recvd *= 10;
      Serial.println(0);
      recvd += 0;
    }
    else if (results.value == 0x488F3CBB){
      Serial.print("Angle:");
      Serial.println(recvd % 181);
      servo.write(recvd % 181);
      recvd = 0;
    }
    
    irrecv.resume(); // Receive the next value
  }
  
}
