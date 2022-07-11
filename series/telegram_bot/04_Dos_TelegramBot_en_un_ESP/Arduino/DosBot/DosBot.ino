// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "CTBot.h"

CTBot miBot1;
CTBot miBot2;

#include "token.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Bot de Telegram");

  miBot1.wifiConnect(ssid, password);

  miBot1.setTelegramToken(token1);
  miBot2.setTelegramToken(token2);

  if (miBot1.testConnection()) {
    Serial.println("Conectado Bot1");
  }
  else {
    Serial.println("Problemas con Bot1");
  }

  if (miBot2.testConnection()) {
    Serial.println("Conectado Bot2");
  }
  else {
    Serial.println("Problemas con Bot1");
  }
}

void loop() {
  TBMessage msg;

  if (CTBotMessageText == miBot1.getNewMessage(msg)) {
    Serial << "Mensaje Bot1: " << msg.sender.firstName << " - " <<  msg.text << "\n";
    miBot1.sendMessage(msg.sender.id, msg.text);
  }

  if (CTBotMessageText == miBot2.getNewMessage(msg)) {
    Serial << "Mensaje Bot2: " << msg.sender.firstName << " - " <<  msg.text << "\n";
    miBot2.sendMessage(msg.sender.id, msg.text);
  }


  delay(250);
}
