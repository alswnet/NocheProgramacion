#include "RTClib.h"

//RTC_DS1307 rtc;
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("No encontrado RTC");
    Serial.flush();
    while (1) delay(10);
  }
}

void loop() {
  DateTime tiempo = rtc.now();

  /*
    | specifier | output                                                 |
    |-----------|--------------------------------------------------------|
    | YYYY      | the year as a 4-digit number (2000--2099)              |
    | YY        | the year as a 2-digit number (00--99)                  |
    | MM        | the month as a 2-digit number (01--12)                 |
    | MMM       | the abbreviated English month name ("Jan"--"Dec")      |
    | DD        | the day as a 2-digit number (01--31)                   |
    | DDD       | the abbreviated English day of the week ("Mon"--"Sun") |
    | AP        | either "AM" or "PM"                                    |
    | ap        | either "am" or "pm"                                    |
    | hh        | the hour as a 2-digit number (00--23 or 01--12)        |
    | mm        | the minute as a 2-digit number (00--59)                |
    | ss        | the second as a 2-digit number (00--59)                |
  */

  char formato1[] = "hh:mm ap";
  Serial.println(tiempo.toString(formato1));

  char formato2[] = "DD/MM/YY-hh:mm:ss";
  Serial.println(tiempo.toString(formato2));

  char formato3[] = "hoy es DDD, DD MMM YYYY";
  Serial.println(tiempo.toString(formato3));

  char formato4[] = "DD/MM/YYYY";
  Serial.println(tiempo.toString(formato4));

  Serial.println();

  delay(10000);
}
