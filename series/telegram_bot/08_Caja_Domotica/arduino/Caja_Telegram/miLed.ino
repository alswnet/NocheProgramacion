#include <Ticker.h>

Ticker cambiarLed;
boolean estadoLed = false;

void configurarLed() {
  pinMode(pinLed, OUTPUT);
  actualizarLed();
}

void funcionLed() {
  estadoLed = !estadoLed;
  digitalWrite(pinLed, estadoLed);
}

void actualizarLed() {
  if (estado != estadoAnterior) {
    Serial << "Cambiando Estado: " << estado << "\n";
    TelnetStream << "Cambiando Estado: " << estado << "\n";

    estadoAnterior = estado;

    switch (estado) {
      case noWifi:
        cambiarLed.attach(0.1, funcionLed);
        break;
      case noBot:
        cambiarLed.attach(1, funcionLed);
        break;
      case conectado:
        cambiarLed.attach(2, funcionLed);
        break;
      default:
        estado = noWifi;
        break;
    }
  }
}