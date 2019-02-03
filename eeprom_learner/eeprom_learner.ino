#include <EEPROM.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  //EEPROM[255] = 0xFF;
  for(int i = 1; i <= 1024;i++) {
    Serial.print(EEPROM[i -1],HEX);
    Serial.print(" ");
    if( i % 64 == 0)  Serial.println();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
