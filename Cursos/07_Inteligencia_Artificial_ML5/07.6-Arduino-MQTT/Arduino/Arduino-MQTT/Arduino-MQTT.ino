int Led = 13;

void setup() {
  pinMode(Led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'H') {
      digitalWrite(Led, HIGH);
    }
    else if (Letra == 'L') {
      digitalWrite(Led, LOW);
    }
  }
}
