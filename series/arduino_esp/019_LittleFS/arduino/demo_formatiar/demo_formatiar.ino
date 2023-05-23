#include "LittleFS.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n\nIniciando de LittleFS");

#if defined(ESP32)
  if (!LittleFS.begin(true)) {
    Serial.println("Error formatiando");
    return;
  }
#endif

  if (!LittleFS.format()) {
    Serial.println("Error formatiando");
    return;
  } else {
    Serial.println("Se boro todo");
  }

  Serial.println("Listo de LittleFS");

  LittleFS.end();
}

void loop() {

}
