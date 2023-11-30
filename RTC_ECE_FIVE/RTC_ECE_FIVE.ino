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
int mode = 0; // modes: 0 (time), 1 (set time), 2 (set alarm)

void setup() {
  URTCLIB_WIRE.begin();
  rtc.set(0, 45, 12, 4, 30, 11, 23);

  lcd.begin(16, 2);
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

void loop() {
  
  if (digitalRead(modeButton) == HIGH) {
    // default values
    uint8_t newMonth = 1, newDay = 1, newYear = 0, newHr = 0, newMin = 0, newSec = 0; 

    lcd.clear(); // clears LCD
    displayTime(newMonth, newDay, newYear, newHr, newMin, newSec);

    // In the following for loop, mode 1 represents month, 2 represents day, 
    // 3 represents year, 4 represents hour, 5 represents minute, 6 represents second
    // When you set time, you have 5 seconds to do so per "mode"

    delay(2000);
    // if (digitalRead(upButton) == HIGH) {
  
      
    // } else if (digitalRead(downButton) == HIGH) {
      
    // }
    
    rtc.set(newSec, newMin, newHr, rtc.dayOfWeek(), newDay, newMonth, newYear);
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
//   } 

//    if (clickDown == HIGH) {
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

