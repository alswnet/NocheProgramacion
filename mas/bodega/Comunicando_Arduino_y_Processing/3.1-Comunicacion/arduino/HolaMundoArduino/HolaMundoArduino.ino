// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

int LedPin = 5;
boolean EstadoLed = false;

void setup() {
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin, EstadoLed);
}

void loop() {

  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'a') {
      EstadoLed = !EstadoLed;
    }
    digitalWrite(LedPin, EstadoLed);
  }
}
