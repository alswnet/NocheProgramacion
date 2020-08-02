#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 2);

int Led1 = 8;
int Led2 = 9;
int Nivel1 = 0;
int Nivel2 = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(Led1, OUTPUT);
  analogWrite(Led1, Nivel1);
  pinMode(Led2, OUTPUT);
  analogWrite(Led2, Nivel2);
}

void loop() {
  if (BTSerial.available()) {
    DecodificarSerial();
  }
  analogWrite(Led1, Nivel1);
  analogWrite(Led2, Nivel2);
  delay(50);
}

void DecodificarSerial() {
  // Mensaje de la forma L1/123
  // Donde L1 Es Led 1
  // 123 el valor intensidad del LED
  String Mensaje = BTSerial.readStringUntil('\n');
  Serial.println("Mensaje: ");
  Serial.println(Mensaje);
  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();
  String Dato = Mensaje.substring(0, PosicionPleca);
  int Valor = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea).toInt();
  if (Dato.equals("L1")) {
    Nivel1 = Valor;
  }
  else if (Dato.equals("L2")) {
    Nivel2 = Valor;
  }

  Serial.print("Dato:");
  Serial.print(Dato);
  Serial.print(" Valor:");
  Serial.print(Valor);
  Serial.println();

}
