#include "Arduino.h"
#include "uRTCLib.h"
#include <Wire.h>
#include <LiquidCrystal.h>
// Include libraries

const int RSPin = 1, EPin = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // LCD pins
const int modeButton = 8, upButton = 9, downButton = 10; // button pins
const int buzzerPin = 11; // buzzer pin
const uint8_t alarm = URTCLIB_ALARM_1;

LiquidCrystal lcd(RSPin, EPin, d4, d5, d6, d7); // Initialize LCD
uRTCLib rtc(0x68); // Initialize RTC

uint8_t date[] = {1, 1, 0, 0, 0, 0};

uint8_t alarmHour, alarmMin, alarmSec; // Time for the Alarm
int mode = 0; // modes: 1 (set time), 2 (set alarm)
// clicking button increments mode

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

  if (rtc.alarmTriggered(alarm)) {
    playAlarm();
  }

  if (digitalRead(modeButton) == HIGH) {
    mode++;
    if (mode == 1) {
      // default values
      // date includes the new Month, day, year, hour, minute, and second, respectively

      lcd.clear(); // clears LCD
      displayTime(date[0], date[1], date[2], date[3], date[4], date[5]);

      // In the following for loop, mode 0 represents month, 1 represents day, 
      // 2 represents year, 3 represents hour, 4 represents minute, 5 represents second
      // When you set time, you have 5 seconds to do so per "mode"
      setTime();
    } else {
      setAlarmTime();
    }
    mode = 0;
  } else {
    displayTime(rtc.month(), rtc.day(), rtc.year(), rtc.hour(), rtc.minute(), rtc.second());
    delay(1000);
  }
}

void setTime() {
  for (int i = 0; i < 6; i++) {
    delay(5000);
    if (digitalRead(upButton) == HIGH) {
      date[i]++;
      date[i] = checkTime(i, date[i]);
      displayTime(date[0], date[1], date[2], date[3], date[4], date[5]); // display incremented time
    } else if (digitalRead(downButton) == HIGH) {
      date[i]--;
      date[i] = checkTime(i, date[i]);
      displayTime(date[0], date[1], date[2], date[3], date[4], date[5]); // display decremented time
    }
  }
  rtc.set(date[0], date[1], date[2], rtc.dayOfWeek(), date[3], date[4], date[5]);
  resetDate();
}

void resetDate() {
  for (int i = 0; i < 6; i++) {
    if (i == 1 || i == 2) {
      date[i] = 1;
    } else {
      date[i] = 0;
    }
  }
}

void setAlarmTime() {
  for (int i = 3; i < 6; i++) {
    delay(5000);
    if (digitalRead(upButton) == HIGH) {
      date[i]++;
      date[i] = checkTime(i, date[i]);
      displayTime(rtc.month(), rtc.day(), rtc.year(), date[3], date[4], date[5]);
    } else if (digitalRead(downButton) == HIGH) {
      date[i]--;
      date[i] = checkTime(i, date[i]);
    }
    rtc.alarmSet(URTCLIB_ALARM_TYPE_1_NONE, date[5], date[4], date[3], rtc.dayOfWeek());
    resetDate();
  }
}

// check if time input is valid
int checkTime(int entry, int tempTime) {
  switch (entry) {
    case 0:
      if (tempTime >= 0) {
        tempTime = tempTime % 12 + 1;
      } else {
        tempTime = 12 + tempTime;
      }
      break;
    case 1:
      if (tempTime >= 0) {
        tempTime = tempTime % 31 + 1;
      } else {
        tempTime = 30 + tempTime;
      }
      break;
    case 2:
      if (tempTime >= 0) {
        tempTime = tempTime % 99 + 1;
      } else {
        tempTime = 99 + tempTime;
      }
      break;
    case 3:
      if (tempTime >= 0) {
        tempTime = tempTime % 12 + 1;
      } else {
        tempTime = 12 + tempTime;
      }
      break;
    case 4:
      if (tempTime >= 0) {
        tempTime = tempTime % 60;
      } else {
        tempTime = 60 + tempTime;
      }
      break;
    case 5:
      if (tempTime >= 0) {
        tempTime = tempTime % 60;
      } else {
        tempTime = 60 + tempTime;
      }
      break;
  }
  return tempTime;
}

void playAlarm() {
    tone(buzzerPin,659.255);
    delay(500);
    tone(buzzerPin,587.33);
    delay(500);
    tone(buzzerPin,523.251);
    delay(500);
    tone(buzzerPin,587.33);
    delay(400);
    
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(10);
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(50);
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(400);
    
    
    tone(buzzerPin,587.33);
    delay(500);
    noTone(buzzerPin);
    delay(10);
    tone(buzzerPin,587.33);
    delay(500);
    noTone(buzzerPin);
    delay(50);
    tone(buzzerPin,587.33);
    delay(500);
    noTone(buzzerPin);
    delay(400);

    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(10);
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(50);
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(400);

    tone(buzzerPin,659.255);
    delay(500);
    tone(buzzerPin,587.33);
    delay(500);
    tone(buzzerPin,523.251);
    delay(500);
    tone(buzzerPin,587.33);
    delay(400);
  //  THIS PART WORKS
    
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(10);
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(50);
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(400);

    tone(buzzerPin,587.33);
    delay(500);
    noTone(buzzerPin);
    delay(10);
    tone(buzzerPin,587.33);
    delay(500);
    noTone(buzzerPin);
    delay(50);
    
    tone(buzzerPin,659.255);
    delay(500);
    noTone(buzzerPin);
    delay(10);
    tone(buzzerPin,587.33);
    delay(500);
    noTone(buzzerPin);
    delay(10);
    tone(buzzerPin,523.251);
    delay(500);
    noTone(buzzerPin);
    delay(1000);
}

