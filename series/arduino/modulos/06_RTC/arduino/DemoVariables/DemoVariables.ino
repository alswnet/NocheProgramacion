#include "RTClib.h"

RTC_DS1307 rtc;
//RTC_DS3231 rtc;

String NombresDia[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
String NombresMes[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

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

  int Anno = tiempo.year();
  int Mes = tiempo.month();
  int Dia = tiempo.day();
  int Hora = tiempo.hour();
  int Hora24 = tiempo.twelveHour();
  int Minuto = tiempo.minute();
  int Segundo = tiempo.second();
  int EsPM = tiempo.isPM();
  int DiaSemana = tiempo.dayOfTheWeek();

  Serial.print(Dia);
  Serial.print('/');
  Serial.print(Mes);
  Serial.print('/');
  Serial.print(Anno);
  Serial.print(' ');
  Serial.print(Hora24);
  Serial.print(':');
  Serial.print(Minuto);
  Serial.print(':');
  Serial.print(Segundo);
  Serial.print(' ');
  Serial.print(EsPM ? "PM" : "AM");
  Serial.println();

  Serial.print(NombresDia[DiaSemana]);
  Serial.print(", ");
  Serial.print(Dia);
  Serial.print(" de ");
  Serial.print(NombresMes[Mes - 1]);
  Serial.print(" del ");
  Serial.print(Anno);
  Serial.println();

  Serial.println();

  delay(5000);
}
