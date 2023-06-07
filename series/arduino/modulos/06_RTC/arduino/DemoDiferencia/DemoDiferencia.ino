#include "RTClib.h"

RTC_DS1307 rtc;
//RTC_DS3231 rtc;

String NombresDia[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
String NombresMes[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

DateTime TiempoEncendido;

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("No encontrado RTC");
    Serial.flush();
    while (1) delay(10);
  }

  TiempoEncendido = rtc.now();
}

void MostrarFecha(const char* Titulo, const DateTime& Fecha) {
  int Anno = Fecha.year();
  int Mes = Fecha.month();
  int Dia = Fecha.day();
  int Hora = Fecha.hour();
  int Hora24 = Fecha.twelveHour();
  int Minuto = Fecha.minute();
  int Segundo = Fecha.second();
  int EsPM = Fecha.isPM();
  int DiaSemana = Fecha.dayOfTheWeek();

  Serial.print(Titulo);
  Serial.print(" -- ");
  Serial.print(NombresDia[DiaSemana]);
  Serial.print(", ");
  Serial.print(Dia);
  Serial.print(" de ");
  Serial.print(NombresMes[Mes - 1]);
  Serial.print(" del ");
  Serial.print(Anno);
  Serial.print(", ");
  Serial.print(Hora24);
  Serial.print(':');
  Serial.print(Minuto < 10 ? "0" : "");
  Serial.print(Minuto);
  Serial.print(' ');
  Serial.print(EsPM ? "PM" : "AM");
  Serial.println();
}

void MostarDiferencia(const char* Titulo, const TimeSpan& Diferencia) {
  Serial.print(Titulo);
  Serial.print(" -- ");
  Serial.print(Diferencia.days());
  Serial.print(" Dias ");
  Serial.print(Diferencia.hours());
  Serial.print(" Horas ");
  Serial.print(Diferencia.minutes());
  Serial.print(" Minutos ");
  Serial.print(Diferencia.seconds());
  Serial.print(" Segundos (");
  Serial.print(Diferencia.totalseconds());
  Serial.print(" total Segundos)");
  Serial.println();
}

void loop() {
  DateTime FechaHoy = rtc.now();
  DateTime Fecha1(2014, 2, 12, 0, 0, 0);
  DateTime Fecha2(1392163200);
  DateTime Fecha3("2014-02-12T00:00:0");
  DateTime FuturoHora(FechaHoy.unixtime() + 1 * 60 * 60);
  DateTime FuturoHoraMedia = FechaHoy + TimeSpan(0, 1, 30, 0);

  TimeSpan UnDia(1, 0, 0, 0);
  DateTime FuturoUnDia = FechaHoy + UnDia;
  DateTime PasadoUnDia = FechaHoy - UnDia;

  TimeSpan DiferenciaVivo = FechaHoy - Fecha1;
  TimeSpan DiferenciaEncendido = FechaHoy - TiempoEncendido;

  MostrarFecha("Hoy", FechaHoy);
  Serial.print("Hoy en Tiempo Unix -- ");
  Serial.print(FechaHoy.unixtime());
  Serial.println(" Segundos");
  MostrarFecha("Canal", Fecha1);
  MostrarFecha("Canal2", Fecha2);
  MostrarFecha("Canal3", Fecha3);
  MostrarFecha("Una Hora Mas", FuturoHora);
  MostrarFecha("Hora y Media Mas", FuturoHoraMedia);
  MostrarFecha("Una Dia Mas", FuturoUnDia);
  MostrarFecha("Un Das Menos", PasadoUnDia);
//
  MostarDiferencia("Tiempo Online", DiferenciaVivo);
  MostarDiferencia("Tiempo encendido", DiferenciaEncendido);

  Serial.println();

  delay(5000);
}
