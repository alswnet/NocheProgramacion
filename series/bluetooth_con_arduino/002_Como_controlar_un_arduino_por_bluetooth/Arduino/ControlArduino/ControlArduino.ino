#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

int Led = 13;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(Led, OUTPUT);
}

void loop() {
  if (BTSerial.available()) {
    char Mensaje = BTSerial.read();
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
