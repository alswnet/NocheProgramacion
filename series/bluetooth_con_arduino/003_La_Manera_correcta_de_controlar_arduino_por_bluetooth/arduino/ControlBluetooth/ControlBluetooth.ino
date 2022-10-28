// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

int Led1 = 5;
int Led2 = 6;
int Nivel1 = 0;
int Nivel2 = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  analogWrite(Led1, Nivel1);
  analogWrite(Led2, Nivel2);
}

void loop() {
  if (BTSerial.available()) {
    DecodificarSerial();
    analogWrite(Led1, Nivel1);
    analogWrite(Led2, Nivel2);
  }
}

void DecodificarSerial() {
  // L1/100 \n
  // L1 es valor
  // 100 es numero

  String Mensaje = BTSerial.readStringUntil('\n');
  Serial.print("Mensaje : ");
  Serial.println(Mensaje);
  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();

  String Dato = Mensaje.substring(0, PosicionPleca);
  int Valor = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea).toInt();

  if (Dato.equals("L1")) {
    Nivel1 = Valor;
  } else if (Dato.equals("L2")) {
    Nivel2 = Valor;
  }

  Serial.print("D : ");
  Serial.print(Dato);
  Serial.print(" V : ");
  Serial.println(Valor);
}
