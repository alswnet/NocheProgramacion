// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

int CanitdadLed = 10;
int LedInicial = 3;
int Esperar = 100;

void setup() {
  for (int i = LedInicial; i < CanitdadLed + LedInicial; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = LedInicial; i < CanitdadLed + LedInicial; i++) {
    digitalWrite(i , HIGH);
    delay(Esperar);
    digitalWrite(i, LOW);
  }

  for (int i = CanitdadLed + LedInicial - 1 ; i >= LedInicial; i--) {
    digitalWrite(i , HIGH);
    delay(Esperar);
    digitalWrite(i, LOW);
  }
}
