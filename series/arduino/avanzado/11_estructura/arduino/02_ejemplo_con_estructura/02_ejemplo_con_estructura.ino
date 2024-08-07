

#define cantidadLed 5

struct led {
  int pin;
  long tiempo;
};

led leds[cantidadLed] = {
  { 2, 300 },
  { 3, 1000 },
  { 4, 400 },
  { 5, 1500 },
  { 6, 1200 }
};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < cantidadLed; i++) {
    pinMode(leds[i].pin, OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < cantidadLed; i++) {
    digitalWrite(leds[i].pin, HIGH);
    delay(leds[i].tiempo);
    digitalWrite(leds[i].pin, LOW);
  }
}
