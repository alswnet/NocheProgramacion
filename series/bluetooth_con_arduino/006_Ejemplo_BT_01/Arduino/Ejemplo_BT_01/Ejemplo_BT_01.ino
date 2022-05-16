// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

#define CantidadLed 10
int Led[CantidadLed] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
boolean EstadoLed[CantidadLed] = {false, false, false, false, false, false, false, false, false, false};


void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  for (int i = 0; i < CantidadLed; i++) {
    pinMode(Led[i], OUTPUT);
    digitalWrite(Led[i], LOW);
  }
}

void loop() {
  if (BTSerial.available()) {
    DecodificarSerial();
  }
}

void DecodificarSerial() {
  // ID/Estado\n
  // ID numero de les
  // Estado
  //   e = encendido
  //   a = apagado
  //   c = cambio

  String Mensaje = BTSerial.readStringUntil('\n');
  Serial.print("Mensaje : ");
  Serial.println(Mensaje);
  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();

  int ID = Mensaje.substring(0, PosicionPleca).toInt();
  String Estado = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea);

  if (Estado.equals("e")) {
    EstadoLed[ID] = true;
  } else if (Estado.equals("a")) {
    EstadoLed[ID] = false;
  } else if (Estado.equals("c")) {
    EstadoLed[ID] = !EstadoLed[ID];
  }

  if (EstadoLed[ID]) {
    digitalWrite(Led[ID], HIGH);
  } else {
    digitalWrite(Led[ID], LOW);
  }

  Serial.print("Led: ");
  Serial.print(ID);
  Serial.print(" E: ");
  Serial.println(Estado);
}
