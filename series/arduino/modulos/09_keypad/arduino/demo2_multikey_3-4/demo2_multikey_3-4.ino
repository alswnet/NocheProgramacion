
#include <Keypad.h>

#define filas 4
#define columnas 3

byte pinesFilas[filas] = { 9, 8, 7, 6 };
byte pinesColumnas[columnas] = { 5, 4, 3 };

char signos[filas][columnas] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

Keypad teclado = Keypad(makeKeymap(signos), pinesFilas, pinesColumnas, filas, columnas);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (teclado.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      if (teclado.key[i].stateChanged) {
        switch (teclado.key[i].kstate) {
          case PRESSED:
            Serial.print("Tecla ");
            Serial.print(teclado.key[i].kchar);
            Serial.println(" Precionar");
            break;
          case HOLD:
            Serial.print("Tecla ");
            Serial.print(teclado.key[i].kchar);
            Serial.println(" Mantener");
            break;
          case RELEASED:
            Serial.print("Tecla ");
            Serial.print(teclado.key[i].kchar);
            Serial.println(" Soltar");
            break;
            // case IDLE:
            // Serial.print("Tecla ");
            // Serial.print(teclado.key[i].kchar);
            // Serial.println(" Soltar");
            // break;
        }
      }
    }
  }
}
