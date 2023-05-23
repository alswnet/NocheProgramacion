#include "LittleFS.h"


void setup() {
  Serial.begin(115200);
  Serial.println("\n\nIniciando de LittleFS");

  if (!LittleFS.begin()) {
    Serial.println("Error montando LittleFS");
    return;
  }

  Serial.println("Demo de LittleFS");

  LittleFS.end();
}

void loop() {

}
