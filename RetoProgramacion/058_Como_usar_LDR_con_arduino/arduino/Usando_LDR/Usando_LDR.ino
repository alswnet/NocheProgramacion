// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

int Led = 13;
int LDR = A0;
int Max, Min;

#include <EEPROM.h>

void setup() {
  pinMode(Led, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(9600);
  Max = EEPROM.read(1)*4;
  Min = EEPROM.read(2)*4;
}

void loop() {
  Serial.print(Max);
  Serial.print(" - ");
  Serial.print(Min);
  Serial.print(" - ");
  Serial.println(analogRead(LDR));

  int ValorActual = analogRead(LDR);

  if (ValorActual <= (Max + Min ) / 2) {
    digitalWrite(Led, 1);
  }
  else {
    digitalWrite(Led, 0);
  }


  if (Max < ValorActual) {
    Max = ValorActual;
    EEPROM.write(1, Max / 4);
  }

  if (Min > ValorActual) {
    Min = ValorActual;
    EEPROM.write(2, Min / 4);
  }
}
