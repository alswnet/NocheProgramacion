// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "CTBot.h"
CTBot miBot;

#include "token.h"

float tiempo = 0;
int id = 0;
char mensaje[50];
void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Bot de Telegram");

  miBot.wifiConnect(ssid, password);

  miBot.setTelegramToken(token);

  if (miBot.testConnection()) {
    Serial.println("\n Conectado");
  }
  else {
    Serial.println("\n Problemas Auxilio");
  }
}

void loop() {

  if (millis() - tiempo > 5000) {
    Serial << "Enviando numero " << id << "\n";
    snprintf(mensaje, 100, "Mensaje: %d", id);
    miBot.sendMessage(IDchat, mensaje);
    id++;
    tiempo = millis();
  }

}
