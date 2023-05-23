
template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "LittleFS.h"

void leerArchivo(const char *ruta) {
  Serial << "Leer en archivo: " << ruta << "\n";

  File archivo = LittleFS.open(ruta, "r");
  if (!archivo) {
    Serial.println("Archivo no se puede abir");
    return;
  }

  Serial.print("Contiene: ");
  while (archivo.available()) {
    String Mensaje = archivo.readString();
    int Entero = Mensaje.toInt();
    float Decimal = Mensaje.toFloat();
    Serial.println(Decimal + 2);
  }
  Serial.println();
  archivo.close();
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nIniciando de LittleFS");

  if (!LittleFS.begin()) {
    Serial.println("Error montando LittleFS");
    return;
  }
  leerArchivo("/numero.txt");

  LittleFS.end();
}

void loop() {
  // put your main code here, to run repeatedly:

}
