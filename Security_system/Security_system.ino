/*
  Author: Rohan Rao <rohroexperiment@gmail.com>
  File: Security_system.ino
  Description:Security system

*/
/* Pin connections 
 *  Reader:
    *  SDA -> 10 
    *  RST -> 9
    *  SCK -> 13
    *  MOSI -> 
    *  MISO -> 
    *  IRQ -> Not connected
    *  VCC -> 3.3V
    *  GND -> GND
 * Other:
    *  OK LED : +ve -> 6, -ve -> GND through 680Ω resistor   
    *  ERROR LED : +ve -> 7, -ve -> GND through 680Ω resistor   
    *  Buzzer: +ve -> 8, -ve -> GND
    *  Potentiometer: Wiper -> A0 , pin 1 -> GND, pin 2 -> 5v 
*/
#include <SPI.h>              //SPI Library
#include <RFID.h>             //Reader Library
//Pins to control the reader (SS is  slave select,RST is reset)
#define SS_PIN 10
#define RST_PIN 9
//Status LED pins
#define ERROR 7
#define OK 6 
#define BUZZER 8              //Buzzer pin
#define TRIGGER 3             //Motion sensor pin
RFID rfid(SS_PIN, RST_PIN);   //RFID object            
int serNum[5];                //Card Serial Number
/*
Disabled card: {10,58,38,163,181}
Valid cards: {112, 102, 218, 164, 104}
*/
int cards[][5] = {
  {112, 102, 218, 164, 104}
};
volatile int pause;           //Pause (used for card matches)
bool access = false;          //Card match
void activate();              //Prototype for function to switch on buzzer
void setup() {
  pause = 1;                  //Initialize delay
  delay(14000);
  pause = 0;
  SPI.begin();                //Start SPI Communications
  rfid.init();                //Initialize RFID Reader
  pinMode(ERROR, OUTPUT);     //Set this pin to output
  pinMode(OK, OUTPUT);        //Set this pin to output
  pinMode(BUZZER, OUTPUT);    //Set this pin to output
  pinMode(TRIGGER, INPUT);    //Set this pin to input
  attachInterrupt(digitalPinToInterrupt(TRIGGER), activate, RISING); //Attach interrupt to rising edge of pin 3
}

void loop() {
  int delaySuccess = map(analogRead(A0), 0, 1023, 10, 60); //Delay on sucess
  if (rfid.isCard()) { //Detect card
    if (rfid.readCardSerial()) {
      for (int x = 0; x < sizeof(cards); x++) { //Go through list of cards
        for (int i = 0; i < sizeof(rfid.serNum); i++ ) {
          if (rfid.serNum[i] != cards[x][i]) { //Check match
            //End loop and to next card in list
            access = false;
            break;
          } else {
            access = true;
          }
        }
        if (access) break; // End if match
      }
    }
    
    if (access) { // Card match
      digitalWrite(BUZZER, LOW);  //Switch off buzzer
      digitalWrite(OK, HIGH);     //Switch on OK LED 
      digitalWrite(ERROR, LOW);   //Switch off ERROR LED
      pause = 1;                  //Pause
      if (delaySuccess < 33) {    //(Delay fails for values above 32767)
        delay(delaySuccess * 1000);
      }
      else {
        delay(32000);
        delay((delaySuccess - 32) * 1000);
      }
      pause = 0;                   //End pause
      digitalWrite(OK, LOW);      // Switch off OK LED


    }  else { //Card not match
      digitalWrite(OK, LOW);      // Switch off OK LED
      digitalWrite(BUZZER, HIGH); // Switch on buzzer
      for (int i = 0; i < 3; i++) { // Flash ERROR LED
        digitalWrite(ERROR, HIGH);
        delay(500);
        digitalWrite(ERROR, LOW);
        delay(500);
      }
    }
  }

  rfid.halt(); //Reset reader for next loop

}
void activate () {
  if (pause == 0 & digitalRead(TRIGGER)) { // Check if not paused and TRIGGER is HIGH
    delayMicroseconds(10000); //Wait 10 ms / 10000 μs 
    if (digitalRead(TRIGGER)) { //Check again
      digitalWrite(BUZZER, HIGH);// Activate buzzer
    }

  }
}
