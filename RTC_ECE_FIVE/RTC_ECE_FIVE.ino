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

void setup() {
  URTCLIB_WIRE.begin();
  rtc.set(0, 57, 12, 7, 22, 11, 23);

  lcd.begin(16, 2);
}

void loop() {
  
  if (digitalRead(modeButton) == HIGH) {
    // default values
    uint8_t newMonth = 1, newDay = 1, newYear = 0, newHr = 0, newMin = 0, newSec = 0; 

    lcd.clear(); // clears LCD
    displayTime(newMonth, newDay, newYear, newHr, newMin, newSec);

    // In the following for loop, mode 1 represents month, 2 represents day, 
    // 3 represents year, 4 represents hour, 5 represents minute, 6 represents second
    // When you set time, you have 5 seconds to do so per "mode"
    for (int mode = 1; mode <= 6; mode++) {
      delay(5000);
      if (digitalRead(upButton) == HIGH) {
        switch (mode) {
          case 1:
            displayTime(newMonth+1, newDay, newYear, newHr, newMin, newSec);
            break;
          case 2:
            displayTime(newMonth, newDay+1, newYear, newHr, newMin, newSec);
            break;
          case 3:
            displayTime(newMonth, newDay, newYear+1, newHr, newMin, newSec);
            break;
          case 4:
            displayTime(newMonth, newDay, newYear, newHr+1, newMin, newSec);
            break;
          case 5:
            displayTime(newMonth, newDay, newYear, newHr, newMin+1, newSec);
            break;
          case 6:
            displayTime(newMonth, newDay, newYear, newHr, newMin, newSec+1);
            break;
        }
      } else if (digitalRead(downButton) == HIGH) {
        switch (mode) {
        case 1:
          displayTime(newMonth-1, newDay, newYear, newHr, newMin, newSec);
          break;
        case 2:
          displayTime(newMonth, newDay-1, newYear, newHr, newMin, newSec);
          break;
        case 3:
          displayTime(newMonth, newDay, newYear-1, newHr, newMin, newSec);
          break;
        case 4:
          displayTime(newMonth, newDay, newYear, newHr-1, newMin, newSec);
          break;
        case 5:
          displayTime(newMonth, newDay, newYear, newHr, newMin-1, newSec);
          break;
        case 6:
          displayTime(newMonth, newDay, newYear, newHr, newMin, newSec-1);
          break;
      }
    }
    rtc.set(newSec, newMin, newHr, rtc.dayOfWeek(), newDay, newMonth, newYear);
    displayTime(rtc.month(), rtc.day(), rtc.year(), rtc.hour(), rtc.minute(), rtc.second());
  } 
  }
  else {
    displayTime(rtc.month(), rtc.day(), rtc.year(), rtc.hour(), rtc.minute(), rtc.second());
    delay(1000);
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
