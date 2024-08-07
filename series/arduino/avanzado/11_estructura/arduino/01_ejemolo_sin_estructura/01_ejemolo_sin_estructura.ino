

#define cantidadLed 5
int pinLed[cantidadLed] = { 2, 3, 4, 5, 6 };
long tiempoLed[cantidadLed] = { 300, 1000, 400, 1500, 1200 };

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < cantidadLed; i++) {
    pinMode(pinLed[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < cantidadLed; i++) {
    digitalWrite(pinLed[i], HIGH);
    delay(tiempoLed[i]);
    digitalWrite(pinLed[i], LOW);
  }
}
