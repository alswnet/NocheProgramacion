#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial

int Led = 13;// I/O donde esta conectado el led

SoftwareSerial BTSerial(3, 2); // RX | TX Poner los pines que usas 

void setup() {
  pinMode(Led, OUTPUT);
  BTSerial.begin(9600);//Inicializar comunicacion
}

void loop() {
  while (BTSerial.available()) {
    char data = (char)BTSerial.read();
    if ( data == 'H')
      digitalWrite(Led, 1);
    else if ( data == 'L')
      digitalWrite(Led, 0);
  }
}
