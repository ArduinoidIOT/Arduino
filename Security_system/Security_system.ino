

#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);
int buzzer = 8;
int trig = 3; 
int serNum[5];
int cards[][5] = {
  {10,58,38,163,181},
  {112,102,218,164,104}

};
int trigged = 0;
//int   = 0;
volatile int pause;
bool access = false;

void setup(){
    
    pause = 1;
    delay(32767);
    delay(60000-32767);
    pause = 0;
    SPI.begin();
    rfid.init();
    
    pinMode(buzzer, OUTPUT);
    pinMode(trig, INPUT);
    Serial.begin(9600);
   attachInterrupt(digitalPinToInterrupt(trig),activate,RISING);
}

void loop(){
    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                      

                  }
              }
              if(access) break;
            }
           
        }
        
       if(access){
        digitalWrite(buzzer,LOW);
          pause = 1;
          delay(15000);
          pause=0;
          

      }        
    }
    
    rfid.halt();

}
void activate () {
  if(pause == 0 & digitalRead(trig)) {
            delayMicroseconds(10000);
            if (digitalRead(trig)) {
            digitalWrite(buzzer,HIGH);}

  }  
}
