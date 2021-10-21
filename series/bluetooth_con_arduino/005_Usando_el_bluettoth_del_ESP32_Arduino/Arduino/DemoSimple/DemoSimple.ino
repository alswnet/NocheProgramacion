// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int Led = 5;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32test");
  pinMode(Led, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    char Mensaje = SerialBT.read();
    if (Mensaje == 'A') {
      digitalWrite(Led, HIGH);
      Serial.println("Encender Led");
    }
    else if (Mensaje == 'B') {
      digitalWrite(Led, LOW);
      Serial.println("Apagar Led");
    }
  }
}
