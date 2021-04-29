#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int Led1 = 5;
int Led2 = 6;
int Nivel1 = 0;
int Nivel2 = 0;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test");
//  pinMode(Led1, OUTPUT);
//  pinMode(Led2, OUTPUT);
//  analogWrite(Led1, Nivel1);
//  analogWrite(Led2, Nivel2);
}

void loop() {
  if (SerialBT.available()) {
    DecodificarSerial();
    //    analogWrite(Led1, Nivel1);
    //    analogWrite(Led2, Nivel2);
  }
}

void DecodificarSerial() {
  // L1/100 \n
  // L1 es valor
  // 100 es numero

  String Mensaje = SerialBT.readStringUntil('\n');
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
