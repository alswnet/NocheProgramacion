int Led = 13;

void setup() {
  pinMode(Led, OUTPUT);
  digitalWrite(Led, LOW);
  Serial.begin(9600); // Serial de depuracion cable USB
  Serial1.begin(9600); // Serial Bluetooth 1
  Serial2.begin(9600); // Serial Bluetooth 2
  Serial.println("Empezando Sistema");
}

void loop() {
  ActualizarSerial(Serial1);
  ActualizarSerial(Serial2);
}


void ActualizarSerial(HardwareSerial &PuertoSerial) {
  if (PuertoSerial.available()) {
    char Mensaje = PuertoSerial.read();
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
