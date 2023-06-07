#include "RTClib.h"

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
  Serial.print("Temperatura: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");
  Serial.println();
  delay(3000);
}
