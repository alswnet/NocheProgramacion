#include <Keypad.h>

const byte ROWS = 4; //cuatro filas
const byte COLS = 3; //tres columnas 

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //Conectar a los pines de fila del teclado
byte colPins[COLS] = {5, 4, 3}; //Conectarse a los pines de la columna del teclado.

//Crear un objeto de teclado
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();// Lee la clave

  // Imprimir si se presiona la tecla
  if (key){
    Serial.print("Tecla presionada : ");
    Serial.println(key);
  }
}
