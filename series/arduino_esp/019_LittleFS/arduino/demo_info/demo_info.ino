
template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "LittleFS.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n\Midiendo a LittleFS");

  if (!LittleFS.begin()) {
    Serial.println("Error montando LittleFS");
    return;
  }

#if defined(ESP32)
  Serial << "Usado: " <<  (LittleFS.usedBytes() / 1024) << "Kbit Total: " << (LittleFS.totalBytes() / 1024) << "Kbit\n" ;
  Serial << "Porcentaje usado: " << (LittleFS.usedBytes() / LittleFS.totalBytes()) * 100 << "%" << "\n";
#elif defined(ESP8266)
  FSInfo fs_info;
  LittleFS.info(fs_info);
  Serial << "Usado: " <<  (fs_info.usedBytes / 1024) << "Kbit Total: " << (fs_info.totalBytes / 1024) << "Kbit\n" ;
  Serial << "Porcentaje usado: " << (fs_info.usedBytes / fs_info.totalBytes) * 100 << "%" << "\n";
#endif

}

void loop() {

}
