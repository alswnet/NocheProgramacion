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
  TBMessage msg;

  if (CTBotMessageText == miBot.getNewMessage(msg)) {
    Serial << "Nombre: " << msg.sender.firstName << " - " <<  msg.sender.lastName << "\n";
    Serial << "Usuario: " << msg.sender.username << " ID: " << msg.sender.id << "\n";
    miBot.sendMessage(msg.sender.id, "Analizando usuario");
  }

  delay(250);
}
