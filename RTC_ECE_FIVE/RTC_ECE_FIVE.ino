#include "Arduino.h"
#include "uRTCLib.h"
#include <Wire.h>
#include <LiquidCrystal.h>
// Include libraries

const int RSPin = 1, EPin = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // LCD pins
const int modeButton = 8; // button pins

LiquidCrystal lcd(RSPin, EPin, d4, d5, d6, d7); // Initialize LCD
uRTCLib rtc(0x68); // Initialize RTC

uint8_t alarmHour, alarmMin, alarmSec; // Time for the Alarm

void setup() {
  URTCLIB_WIRE.begin();
  rtc.set(00, 30, 2, 7, 19, 11, 23);

  lcd.begin(16, 2);
}

void loop() {
  if (digitalRead(modeButton) == HIGH) {
    lcd.clear();
    digitalWrite(modeButton, LOW);
  } else {
    displayTime();
    delay(1000);
  }
}

void displayTime() {
  rtc.refresh();

  lcd.setCursor(0, 0);
  lcd.print("Date: ");

  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.day());
  lcd.print('/');
  lcd.print(rtc.year());

  lcd.setCursor(0, 1);
  lcd.print("Time: ");

  if (rtc.hour() < 10) {
    lcd.print(0);
    lcd.print(rtc.hour());
  } else {
    lcd.print(rtc.hour());
  }
  lcd.print(':');

  if (rtc.minute() < 10) {
    lcd.print(0);
    lcd.print(rtc.minute());
  } else {
    lcd.print(rtc.minute());
  }
  lcd.print(':');

  if (rtc.second() < 10) {
    lcd.print(0);
    lcd.print(rtc.second());
  } else {
    lcd.print(rtc.second());
  }
}

// void setTime() {
//   // get input from user
//   int tempTimeHrs = 0;
//   int tempTimeMins = 0;
  
//   int clickUp = digitalRead(upPin);
//   int clickDown = digitalRead(downPin);
//   if (clickUp == HIGH) {
//     tempTimeHrs++;    
//   } else if (clickDown == HIGH) {
//     tempTimeHrs--;
    
//   }

//   if (tempTimeHrs >= 0) {
//       tempTimeHrs = tempTimeHrs % 12 + 1;
//   } else {
//       tempTimeHrs = 12 + tempTimeHrs;
//   }
//   // display on LCD

//   if (digitalRead(nextPin) == HIGH) {
//     if (clickUp == HIGH) {
//       tempTimeMins++;
//     } else if (clickDown == HIGH) {
//       tempTimeMins--;
//     }

//     if (tempTimeHrs >= 0) {
//         tempTimeMins = tempTimeMins % 60;
//     } else {
//         tempTimeHrs = 60 + tempTimeHrs;
//     }
//     // display on LCD
//   }
// } 

// void setAlarm() {
//   // get input from user
//   uint8_t tempTimeHrs = 0;
//   uint8_t tempTimeMins = 0;
  
//   int clickUp = digitalRead(upPin);
//   int clickDown = digitalRead(downPin);
//   if (clickUp == HIGH) {
//     tempTimeHrs++;    
//   } else if (clickDown == HIGH) {
//     tempTimeHrs--;
    
//   }

//   if (tempTimeHrs >= 0) {
//       tempTimeHrs = tempTimeHrs % 12 + 1;
//   } else {
//       tempTimeHrs = 12 + tempTimeHrs;
//   }
//   // display on LCD

//   if (digitalRead(nextPin) == HIGH) {
//     if (clickUp == HIGH) {
//       tempTimeMins++;
//     } else if (clickDown == HIGH) {
//       tempTimeMins--;
//     }

//     if (tempTimeHrs >= 0) {
//         tempTimeMins = tempTimeMins % 60;
//     } else {
//         tempTimeHrs = 60 + tempTimeHrs;
//     }
//   }
//   alarmHour = tempTimeHrs;
//   alarmMin = tempTimeMins;
//   alarmSec = 0;
// }

// bool checkAlarm() {
//   return (alarmHour == rtc.hour()) && (alarmMin == rtc.minute()) && (alarmSec = rtc.second());
// }
