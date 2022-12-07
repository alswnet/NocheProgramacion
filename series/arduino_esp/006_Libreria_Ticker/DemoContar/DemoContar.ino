template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include <Ticker.h>

Ticker cambiarContador;

int Contador = 0;

void FuncionContar() {
  Contador++;
  Serial << "El contador va en:  " << Contador << "\n";
  if (Contador >= 10) {
    cambiarContador.detach();
  }
}

void setup() {
  Serial.begin(115200);
  cambiarContador.attach(2, FuncionContar);
}

void loop() {

}
