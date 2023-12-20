#include "LittleFS.h"

void salvarArchivo(String aparato, const char *estado) {
  aparato = "/" + aparato + ".txt";
  char direccion[30];
  aparato.toCharArray(direccion, aparato.length() + 1);

  Serial << "Escribiendo en archivo: " << direccion << ": " << estado << "\n";
  TelnetStream << "Escribiendo en archivo: " << direccion << ": " << estado << "\n";

  LittleFS.begin();
  File archivo = LittleFS.open(direccion, "w");
  if (!archivo) {
    Serial.println("Archivo no se puede abir");
    TelnetStream.println("Archivo no se puede abir");
    return;
  }

  if (!archivo.print(estado)) {
    Serial.println("Error Escribiendo");
    TelnetStream.println("Error Escribiendo");
  }

  archivo.close();
  LittleFS.end();
}

boolean leerArchivo(String aparato) {
  aparato = "/" + aparato + ".txt";
  char direccion[30];
  aparato.toCharArray(direccion, aparato.length() + 1);

  LittleFS.begin();
  File archivo = LittleFS.open(direccion, "r");
  if (!archivo) {
    Serial.println("Archivo no se puede abir");
    return false;
  }

  String Mensaje;
  while (archivo.available()) {
    Mensaje = archivo.readString();
  }
  archivo.close();
  LittleFS.end();

  return Mensaje.equalsIgnoreCase("encendido");
}

void formatiarMemoria(Stream &miSerial) {

#if defined(ESP32)
  if (!LittleFS.begin(true)) {
    Serial.println("Error formatiando");
    return;
  }
#endif

  if (!LittleFS.format()) {
    miSerial.println("Error formatiando");
    return;
  } else {
    miSerial.println("Se boro todo, formatiado LittleFS");
  }
}
