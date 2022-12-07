template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include <Ticker.h>

Ticker cambiarLed;

#if defined(ESP8266)
int led = LED_BUILTIN;
#elif defined(ESP32)
int led = 2;
#endif

boolean estado = false;

void FuncionLed() {
  estado = !estado;
  digitalWrite(led, estado ? HIGH : LOW);
  Serial << "Estado led: " << (estado ? "Encendido" : "Apagado") << "\n";
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  cambiarLed.attach(1.5, FuncionLed);
}

void loop() {

}
