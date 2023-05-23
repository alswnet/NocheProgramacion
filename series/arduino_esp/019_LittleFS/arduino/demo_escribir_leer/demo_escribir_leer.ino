
template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "LittleFS.h"

void escrivirArchivo(const char *ruta, const char *texto) {
  Serial << "Escribiendo en archivo: " << ruta << "\n";

  File archivo = LittleFS.open(ruta, "w");
  if (!archivo) {
    Serial.println("Archivo no se puede abir");
    return;
  }

  if (archivo.print(texto)) {
    Serial.println("Archivo Escribiendo");
  } else {
    Serial.println("Error Escribiendo");
  }
  archivo.close();
}

void leerArchivo(const char *ruta) {
  Serial << "Leer en archivo: " << ruta << "\n";

  File archivo = LittleFS.open(ruta, "r");
  if (!archivo) {
    Serial.println("Archivo no se puede abir");
    return;
  }

  Serial.print("Contiene: ");
  while (archivo.available()) {
    Serial.write(archivo.read());
  }
  Serial.println();
  archivo.close();
}


void agregarArchivo(const char *ruta, const char *texto) {
  Serial << "Agregar en archivo: " << ruta << "\n";

  File archivo = LittleFS.open(ruta, "a");
  if (!archivo) {
    Serial.println("Archivo no se puede abir");
    return;
  }
  if (archivo.print(texto)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  archivo.close();
}

void borrarArchivo(const char *ruta) {
  Serial << "Borrando el arhivo: " << ruta << "\n";

  if (LittleFS.remove(ruta)) {
    Serial.println("Archivo borrado");
  } else {
    Serial.println("Error borrando");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nIniciando de LittleFS");

  if (!LittleFS.begin()) {
    Serial.println("Error montando LittleFS");
    return;
  }

  Serial.println("Iniciando de LittleFS");

  escrivirArchivo("/mensaje.txt", "Dale Like al video");
  agregarArchivo("/mensaje.txt", ", y comparte en video con un amigo");
  leerArchivo("/mensaje.txt");
  borrarArchivo("/mensaje.txt");
  leerArchivo("/secreto.txt");

  LittleFS.end();
}

void loop() {

}
