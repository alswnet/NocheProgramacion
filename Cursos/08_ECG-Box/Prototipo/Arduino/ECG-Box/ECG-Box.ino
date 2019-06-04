#include <SoftwareSerial.h>

SoftwareSerial SerialExtra(10, 11); // RX, TX

int EntradaECG = A0;
int EntradaBateria = A1;
long Tiempo = 0;
long Espera = 1000;
int Envio = 10;
int EnvioTmp = 0;
void setup() {
  Serial.begin(9600);
  SerialExtra.begin(9600);
}


void loop() {

  /*
    Serial.print('E');
    Serial.print(analogRead(EntradaECG));
    Serial.println(';');

    Serial.print('B');
    Serial.print(analogRead(EntradaBateria));
    Serial.println(';');
  */

  SerialExtra.print('E');
  SerialExtra.print(analogRead(EntradaECG));
  SerialExtra.print(';');

  if (millis() > Tiempo + Espera) {
    Tiempo = millis();
    SerialExtra.print('B');
    SerialExtra.print(analogRead(EntradaBateria));
    SerialExtra.print(';');
  }
  delay(Envio);

  /*
    if (Serial.available()) {
     SerialExtra.write(Serial.read());
    }
  */
  while (SerialExtra.available()) {
    char Letra = SerialExtra.read();
    //Serial.write(Letra );
    if (Letra == 'V') {
      EnvioTmp  = 0;
    }
    else if (Letra == ';') {
      Envio = EnvioTmp;
      Serial.print("Velocidad: ");
      Serial.println(Envio);
    }
    else if (Letra >= '0' && Letra <= '9') {
      EnvioTmp = EnvioTmp * 10 + int(Letra - '0');
    }
    delay(10);
  }

}
