// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

int Led = 5;

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
