
#define cantidadLed 5
int pinLed[cantidadLed] = { 2, 3, 4, 5, 6 };
bool estadoLed[cantidadLed] = { false, false, false, false, false };
long tiempoLed[cantidadLed] = { 300, 1000, 400, 1500, 1200 };
long ultimoLed[cantidadLed] = { 0, 0, 0, 0, 0 };

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < cantidadLed; i++) {
    pinMode(pinLed[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < cantidadLed; i++) {
    actualizarLed(pinLed[i], estadoLed[i], tiempoLed[i], ultimoLed[i]);
  }
}


void actualizarLed(int pin, bool &estado, long tiempo, long &ultimo) {
  float tiempoActual = millis();

  if (tiempoActual - ultimo > tiempo) {
    ultimo = tiempoActual;
    estado = !estado;
    if (estado) {
      digitalWrite(pin, HIGH);
    } else {
      digitalWrite(pin, LOW);
    }
  }
}