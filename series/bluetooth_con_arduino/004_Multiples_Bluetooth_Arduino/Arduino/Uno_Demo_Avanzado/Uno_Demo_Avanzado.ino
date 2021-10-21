#include <SoftwareSerial.h>
SoftwareSerial BTSerial1(2, 3);
SoftwareSerial BTSerial2(8, 9);
int Led1 = 5;
int Led2 = 6;
int Nivel1 = 0;
int Nivel2 = 0;

void setup() {
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  analogWrite(Led1, Nivel1);
  analogWrite(Led2, Nivel2);
  Serial.begin(9600); // Serial de depuracion cable USB
  BTSerial1.begin(9600); // Serial Bluetooth 1
  BTSerial2.begin(9600); // Serial Bluetooth 2
  Serial.println("Empezando Sistema");
}

void loop() {
  ActualizarSerial(BTSerial1);
  ActualizarSerial(BTSerial2);

  analogWrite(Led1, Nivel1);
  analogWrite(Led2, Nivel2);
}


void ActualizarSerial(SoftwareSerial &PuertoSerial) {
    if (PuertoSerial.available()) {
  String Mensaje = PuertoSerial.readStringUntil('\n');
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
}
