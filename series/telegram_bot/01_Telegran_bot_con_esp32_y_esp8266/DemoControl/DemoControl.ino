// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "CTBot.h"
CTBot miBot;
int Led = 2;

#include "token.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Bot de Telegram");

  pinMode(Led, OUTPUT);
  digitalWrite(Led, HIGH);

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
    Serial << "Mensaje: " << msg.sender.firstName << " - " <<  msg.text << "\n";

    if (msg.text.equalsIgnoreCase("encender")) {
      Serial.println("Encender Led");
      digitalWrite(Led, HIGH);
      miBot.sendMessage(msg.sender.id, "Led Enendido");
    }
    else if (msg.text.equalsIgnoreCase("apagar")) {
      Serial.println("Apagar Led");
      digitalWrite(Led, LOW);
      miBot.sendMessage(msg.sender.id, "Led Apagado");
    }
    else {
     miBot.sendMessage(msg.sender.id, "Bienbenido " + msg.sender.firstName + ",intenta usar: encender o apagar");
    }
  }

  delay(250);
}
