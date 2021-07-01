// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
