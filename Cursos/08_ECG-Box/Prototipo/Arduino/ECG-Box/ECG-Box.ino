#include <SoftwareSerial.h>

SoftwareSerial SerialExtra(10,11); // RX, TX



void setup() {
  Serial.begin(9600);
  SerialExtra.begin(9600);
}

void loop() {
  if (Serial.available()) {
    SerialExtra.write(Serial.read());
  }

  if (SerialExtra.available()) {
    Serial.write(SerialExtra.read());
  }
}
