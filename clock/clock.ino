// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
const short buzzer = 8;
bool mon = false; 
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
bool highed;
void setup () {
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  lcd.begin(16,2);
  pinMode(buzzer,OUTPUT);
 // if (! rtc.isrunning()) {
   // Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  //}
}

void loop () {
    DateTime now = rtc.now();
    highed=false;
    lcd.setCursor(0,0);
    if(now.dayOfTheWeek() ==0) lcd.print("Sun");
    else if(now.dayOfTheWeek() ==1) lcd.print("Mon");
    else if(now.dayOfTheWeek() ==2) lcd.print("Tue");
    else if(now.dayOfTheWeek() ==3) lcd.print("Wed");
    else if(now.dayOfTheWeek() ==4) lcd.print("Thu");
    else if(now.dayOfTheWeek() ==5) lcd.print("Fri");
    else if(now.dayOfTheWeek() ==6) lcd.print("Sat");
    lcd.print(" ");
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    lcd.setCursor(0,1);
    if ((now.hour() /12 )<10) lcd.print(0);
    lcd.print(now.hour()%12);
    lcd.print(':');
    if (now.minute() < 10) lcd.print(0);
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    if (now.second() < 10) lcd.print(0);
    lcd.print(now.second(), DEC);
    lcd.print(" ");
    if (now.hour() /12 ==1) lcd.print("PM");
    else lcd.print("AM");
    lcd.setCursor(13,1);
    if (analogRead(A0) < 405)lcd.print("(!)");
    else lcd.print("   ");
    if (Serial.available()) {
      String dt =Serial.readString();
      dt.trim();
      if (dt == "monitor") mon = true;
      else if(dt == "!monitor") mon = false;
      
    }
    Serial.println(analogRead(A0));
    
}

