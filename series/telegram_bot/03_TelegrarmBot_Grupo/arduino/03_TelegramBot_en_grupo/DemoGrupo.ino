// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "CTBot.h"
#include "Utilities.h"

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

  if (miBot.getNewMessage(msg)) {
    if (msg.messageType == CTBotMessageText) {
      Serial << "Mensaje: " << msg.sender.firstName << " - " <<  msg.text << "\n";
      Serial << "Titulo: " << msg.group.title << " - " << int64ToAscii(msg.group.id) << "\n";
      //      miBot.sendMessage(msg.sender.id, msg.text);

      if (msg.group.id < 0) {
        miBot.sendMessage(msg.group.id, msg.text);
      }
    }
  }

  delay(500);
}
