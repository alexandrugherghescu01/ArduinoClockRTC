#include "Arduino.h"
#include "uRTCLib.h"
#include <Wire.h>
#include <LiquidCrystal.h>
// Include libraries

const int RSPin = 1, EPin = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // LCD pins
const int modeButton = 8, upButton = 9, downButton = 10; // button pins

LiquidCrystal lcd(RSPin, EPin, d4, d5, d6, d7); // Initialize LCD
uRTCLib rtc(0x68); // Initialize RTC

uint8_t alarmHour, alarmMin, alarmSec; // Time for the Alarm

void setup() {
  URTCLIB_WIRE.begin();
  rtc.set(0, 57, 12, 7, 22, 11, 23);

  lcd.begin(16, 2);
}

void loop() {
  
  if (digitalRead(modeButton) == HIGH) {
    delay(3000);
    uint8_t newMonth = 1, newDay = 1, newYear = 0, newHr = 0, newMin = 0, newSec = 0; // SetAlarm
    int mode = 1; // 1 represents hour, 2 represents minute, 3 represents second

    lcd.clear();
    displayTime(newMonth, newDay, newYear, newHr, newMin, newSec);
    
    // if (digitalRead(upButton) == HIGH) {
    //   switch (mode) {
    //     case 1:
    //       // displayTime(rtc.hour(), rtc.);
    //     case 2:

    //     case 3:

    //     default:
    //       mode = 1;
    //   }
    // } else if (digitalRead(downButton) == HIGH) {

    // }

    // // rtc.set(0, 57, 12, 7, 22, 11, 23);
    // // lcd.clear();
  } else {
    displayTime(rtc.month(), rtc.day(), rtc.year(), rtc.hour(), rtc.minute(), rtc.second());
    delay(1000);
  }
}

void displayTime(uint8_t month, uint8_t day, uint8_t year, uint8_t hour, uint8_t minute, uint8_t second) {
  rtc.refresh();

  lcd.setCursor(0, 0);
  lcd.print("Date: ");

  if (month < 10) {
    lcd.print(0);
  }
  lcd.print(month);
  lcd.print('/');

  if (day < 10) {
    lcd.print(0);
  }
  lcd.print(day);
  lcd.print('/');

  if (year < 10) {
    lcd.print(0);
  }
  lcd.print(year);

  lcd.setCursor(0, 1);
  lcd.print("Time: ");

  if (hour < 10) {
    lcd.print(0);
  }
  lcd.print(hour);
  
  lcd.print(':');

  if (minute < 10) {
    lcd.print(0);
  }
  lcd.print(minute);
  
  lcd.print(':');

  if (second < 10) {
    lcd.print(0);
  }
  lcd.print(second);
  
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
