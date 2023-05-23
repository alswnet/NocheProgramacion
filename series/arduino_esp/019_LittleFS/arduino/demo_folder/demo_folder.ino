template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "LittleFS.h"

void leerFolder(const char *ruta) {
  Serial << "Leyendo en folder: " << ruta << "\n";

#if defined(ESP8266)
  Dir folder = LittleFS.openDir(ruta);
  while (folder.next()) {
    File archivo = folder.openFile("r");
    Serial.print("  Nombre: ");
    Serial.print(archivo.name());
    Serial.print("  Tamaño: ");
    Serial.print(archivo.size());
    Serial.print("  Folder: ");
    Serial.print(archivo.isDirectory() ? "Si" : "No");
    Serial.println();
    archivo.close();
  }
#else defined(ESP32)
  File folder = LittleFS.open(ruta);
  File archivo = folder.openNextFile();
  while (archivo) {
    Serial.print("  Nombre: ");
    Serial.print(archivo.name());
    Serial.print("  Tamaño: ");
    Serial.print(archivo.size());
    Serial.print("  Folder: ");
    Serial.print(archivo.isDirectory() ? "Si" : "No");
    Serial.println();
    archivo = folder.openNextFile();
  }
  archivo.close();
#endif

}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nIniciando de LittleFS");

  if (!LittleFS.begin()) {
    Serial.println("Error montando LittleFS");
    return;
  }

  Serial.println("Demo de LittleFS");

  leerFolder("/");

  LittleFS.end();
}

void loop() {

}
