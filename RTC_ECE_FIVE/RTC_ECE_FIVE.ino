#include "Arduino.h"
#include "uRTCLib.h"
#include <Wire.h> // i2c
#include <LiquidCrystal.h>

const int RSPin = 1;
const int EPin = 2;
const int modePin = 8; // mode
const int upPin = 4; // up
const int downPin = 5; // down
const int nextPin = 6; // next

LiquidCrystal lcd(RSPin, EPin, modePin, upPin, downPin, nextPin);
uRTCLib rtc(0x68);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String modes[3] = {"Time", "SetTime", "SetAlarm"};
int index = 0;
uint8_t alarmHour, alarmMin, alarmSec;

void setup() {
  Serial.begin(9600);
  delay(3000); // wait for console opening

  URTCLIB_WIRE.begin();

  // Comment out below line once you set the date & time.
  // Following line sets the RTC with an explicit date & time
  // for example to set November 11 2023 at 12:56 you would call:
  rtc.set(0, 31, 12, 5, 17, 11, 23);
  // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
  // set day of week (1=Sunday, 7=Saturday)
  pinMode(modePin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(nextPin, INPUT);
}

void loop() {
  rtc.refresh();

    lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print("Current Date & Time: ");
  lcd.print(rtc.year());
  lcd.print('/');
  lcd.print(rtc.month());
  lcd.print('/');
  lcd.print(rtc.day());
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print(rtc.hour());
  lcd.print(':');
  lcd.print(rtc.minute());
  lcd.print(':');
  lcd.print(rtc.second());

  delay(1000);

  int val = digitalRead(modePin);
  if (val == HIGH) {
      index++;
      Serial.print(1); // test
  } else {
      Serial.print(0); 
   }

   if (checkAlarm()) {
      // ring buzzer
   }

   if (modes[index] == "SetTime") {
      setTime();
   } else if (modes[index] == "SetAlarm") {
      setAlarm();
   }
  
  delay(100);

  /*Serial.print("Temperature: ");
  Serial.print(rtc.temp()  / 100);
  Serial.print("\xC2\xB0");   //shows degrees character
  Serial.println("C");

  Serial.println();
  delay(1000);*/
}

void setTime() {
  // get input from user
  int tempTimeHrs = 0;
  int tempTimeMins = 0;
  
  int clickUp = digitalRead(upPin);
  int clickDown = digitalRead(downPin);
  if (clickUp == HIGH) {
    tempTimeHrs++;    
  } else if (clickDown == HIGH) {
    tempTimeHrs--;
    
  }

  if (tempTimeHrs >= 0) {
      tempTimeHrs = tempTimeHrs % 12 + 1;
  } else {
      tempTimeHrs = 12 + tempTimeHrs;
  }
  // display on LCD

  if (digitalRead(nextPin) == HIGH) {
    if (clickUp == HIGH) {
      tempTimeMins++;
    } else if (clickDown == HIGH) {
      tempTimeMins--;
    }

    if (tempTimeHrs >= 0) {
        tempTimeMins = tempTimeMins % 60;
    } else {
        tempTimeHrs = 60 + tempTimeHrs;
    }
    // display on LCD
  }
} 

void setAlarm() {
  // get input from user
  uint8_t tempTimeHrs = 0;
  uint8_t tempTimeMins = 0;
  
  int clickUp = digitalRead(upPin);
  int clickDown = digitalRead(downPin);
  if (clickUp == HIGH) {
    tempTimeHrs++;    
  } else if (clickDown == HIGH) {
    tempTimeHrs--;
    
  }

  if (tempTimeHrs >= 0) {
      tempTimeHrs = tempTimeHrs % 12 + 1;
  } else {
      tempTimeHrs = 12 + tempTimeHrs;
  }
  // display on LCD

  if (digitalRead(nextPin) == HIGH) {
    if (clickUp == HIGH) {
      tempTimeMins++;
    } else if (clickDown == HIGH) {
      tempTimeMins--;
    }

    if (tempTimeHrs >= 0) {
        tempTimeMins = tempTimeMins % 60;
    } else {
        tempTimeHrs = 60 + tempTimeHrs;
    }
  }
  alarmHour = tempTimeHrs;
  alarmMin = tempTimeMins;
  alarmSec = 0;
}

bool checkAlarm() {
  return (alarmHour == rtc.hour()) && (alarmMin == rtc.minute()) && (alarmSec = rtc.second());
}
