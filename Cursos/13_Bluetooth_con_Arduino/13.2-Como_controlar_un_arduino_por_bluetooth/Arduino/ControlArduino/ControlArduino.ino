#include <SoftwareSerial.h>

int Led = 13;

SoftwareSerial BTSerial(2, 3);

void setup() {
  pinMode(Led, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  while (BTSerial.available()) {
    char data = BTSerial.read();
    if ( data == 'A') {
      digitalWrite(Led, 1);
      Serial.println("Encender LED");
    }
    else if ( data == 'B') {
      digitalWrite(Led, 0);
      Serial.println("Apagar LED");
    }
  }
}
