
template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include <Ticker.h>

Ticker cambiador1;
Ticker cambiador2;
Ticker cambiador3;

int contador1 = 0;
int contador2 = 0;
int contador3 = 0;

void Funcion1() {
  contador1++;
  Serial << "Funcion 1: " << contador1 << "\n";
}

void Funcion2() {
  contador2++;
  Serial << "Funcion 2: " << contador2 << "\n";
}

void Funcion3() {
  contador3++;
  Serial << "Funcion 3: " << contador3 << "\n";
}

void setup() {
  Serial.begin(115200);
  cambiador1.attach(1.5, Funcion1);
  cambiador2.attach(0.5, Funcion2);
  cambiador3.attach(2.1, Funcion3);
}

void loop() {

}
