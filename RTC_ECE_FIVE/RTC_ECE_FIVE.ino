#include "Arduino.h"
#include "uRTCLib.h"
#include <Wire.h>
#include <LiquidCrystal.h>
// Include libraries

const int RSPin = 1, EPin = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // LCD pins
const int modeButton = 8, upButton = 9, downButton = 10; // button pins
const int buzzerPin = 11; // buzzer pin

LiquidCrystal lcd(RSPin, EPin, d4, d5, d6, d7); // Initialize LCD
uRTCLib rtc(0x68); // Initialize RTC

uint8_t date[] = {1, 1, 0, 0, 0, 0}; // month, day, year, hour, min, sec

uint8_t alarm[] = {0, 0, 0}; // Time for the Alarm in hr, min, sec
int mode = 0; // modes: 1 (set time), 2 (set alarm)
bool alarmOn = false;
// clicking button increments mode

void setup() {
  URTCLIB_WIRE.begin();
  rtc.set(0, 0, 6, 4, 7, 12, 23);

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

void resetTime() {
  for (int i = 3; i < 6; i++) {
    date[i] = 0;
  }
}

void setTime() {
  lcd.setCursor(15, 1);
  lcd.print("S"); // indicator for set time
  for (int i = 0; i < 6; i++) {
    lcd.setCursor(15, 0);
    lcd.print(i); // print the iteration to denote whether to set month, day, year, hr, min, sec, respectively
    delay(5000);
    if (digitalRead(upButton) == HIGH) { // up button pressed
      tone(buzzerPin,659.255); // tells you if successfully changed time
      delay(500);
      noTone(buzzerPin);
      date[i]++;
      date[i] = checkTime(i, date[i]); // verify time for validity
      displayTime(date[0], date[1], date[2], date[3], date[4], date[5]); // display incremented time
    } else if (digitalRead(downButton) == HIGH) { // down button pressed
      tone(buzzerPin,587.33); // tells you if successfully changed time
      delay(500);
      noTone(buzzerPin);
      date[i]--;
      date[i] = checkTime(i, date[i]);
      displayTime(date[0], date[1], date[2], date[3], date[4], date[5]); // display decremented time
    }
  }
  rtc.set(date[5], date[4], date[3], rtc.dayOfWeek(), date[1], date[0], date[2]); // order: sec, min, hr, dayOfWeek, day, month, year
  lcd.setCursor(15, 0);
  lcd.print(" ");

  lcd.setCursor(15, 1);
  lcd.print(" ");
}

void setAlarmTime() {
  lcd.setCursor(15, 1);
  lcd.print("A"); // indicator for set alarm
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(15, 0);
    lcd.print(i);
    delay(5000);
    if (digitalRead(upButton) == HIGH) {
      tone(buzzerPin,659.255); // tells you if successfully changed time
      delay(500);
      noTone(buzzerPin);
      alarm[i]++;
      alarm[i] = checkTime(i+3, alarm[i]);
      displayTime(rtc.month(), rtc.day(), rtc.year(), alarm[0], alarm[1], alarm[2]);
    } else if (digitalRead(downButton) == HIGH) {
      tone(buzzerPin,587.33);
      delay(500);
      noTone(buzzerPin);
      alarm[i]--;
      alarm[i] = checkTime(i+3, alarm[i]); // tells you if successfully changed time
      displayTime(rtc.month(), rtc.day(), rtc.year(), alarm[0], alarm[1], alarm[2]);
    }
  }
  lcd.setCursor(15, 0);
  lcd.print("D"); // alarm time indicator


  displayTime(rtc.month(), rtc.day(), rtc.year(), alarm[0], alarm[1], alarm[2]);

  lcd.setCursor(15, 0);
  lcd.print(" ");

  lcd.setCursor(15, 1);
  lcd.print(" ");
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

void loop() {
  if (digitalRead(modeButton) == HIGH) {
    mode++;
    if (mode == 1) {
      // date includes the new Month, day, year, hour, minute, and second, respectively

      lcd.clear(); // clears LCD
      displayTime(date[0], date[1], date[2], date[3], date[4], date[5]);

      // In the following for loop, mode 0 represents month, 1 represents day, 
      // 2 represents year, 3 represents hour, 4 represents minute, 5 represents second
      // When you set time, you have 5 seconds to do so per "mode"
      setTime();
    } else if (mode == 2) {
      lcd.clear();
      displayTime(date[0], date[1], date[2], alarm[0], alarm[1], alarm[2]);
      setAlarmTime();
      mode = 0;
    }
  } else {
    displayTime(rtc.month(), rtc.day(), rtc.year(), rtc.hour(), rtc.minute(), rtc.second());
    delay(1000);
  }

    if (rtc.hour() == alarm[0] && rtc.minute() == alarm[1] && rtc.second() == alarm[2]) {
      alarmOn = true;
      while (alarmOn) {
        playAlarm();
        if (digitalRead(modeButton) == HIGH) {
          alarmOn = false;
          mode = 0;
        }
      }
  }
}