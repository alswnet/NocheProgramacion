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

  Serial.println("Configurando la fecha y hora Actual");
  Serial.print("Fecha: ");
  Serial.println(F(__DATE__));
  Serial.print("Hora: ");
  Serial.println(F(__TIME__));
  Serial.println();

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Julio 17, 2023 a las 7:30 am
  // rtc.adjust(DateTime(2023, 7, 17, 7, 30, 0));
}

void loop() {
  DateTime tiempo = rtc.now();

  Serial.println("Completo \t" + tiempo.timestamp(DateTime::TIMESTAMP_FULL));
  Serial.println("Fecha Actual \t" + tiempo.timestamp(DateTime::TIMESTAMP_DATE));
  Serial.println("Hora Actual \t" + tiempo.timestamp(DateTime::TIMESTAMP_TIME));
  Serial.println();

  delay(10000);
}
