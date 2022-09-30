// Creado ChepeCarlos
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include "CTBot.h"

CTBot miBot;
CTBotInlineKeyboard miTeclado;

#include "token.h"
uint8_t led = 2;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Bot Telegram...");

  miBot.wifiConnect(ssid, password);

  miBot.setTelegramToken(token);

  if (miBot.testConnection()) {
    Serial.println("Bot Conectado");
  }
  else {
    Serial.println("Erro con Bot");
  }

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  miTeclado.addButton("Encender", "encender", CTBotKeyboardButtonQuery);
  miTeclado.addButton("Apagar", "apagar", CTBotKeyboardButtonQuery);
  miTeclado.addRow();
  miTeclado.addButton("mira documentación", "https://nocheprogramacion.com/", CTBotKeyboardButtonURL);
}

void loop() {
  TBMessage msg;

  if (miBot.getNewMessage(msg)) {
    if (msg.messageType == CTBotMessageText) {
      if (msg.text.equalsIgnoreCase("opciones")) {
        miBot.sendMessage(msg.sender.id, "Cambiar Led", miTeclado);
      }
      else {
        miBot.sendMessage(msg.sender.id, "prueba 'opciones'");
      }
    } else if (msg.messageType == CTBotMessageQuery) {
      Serial << "Mensaje: " <<  msg.sender.firstName;
      if (msg.callbackQueryData.equals("encender")) {
        Serial.println(" Endender");
        digitalWrite(led, HIGH);
        miBot.endQuery(msg.callbackQueryID, "Led Encendido", true);
      } else if (msg.callbackQueryData.equals("apagar")) {
         Serial.println(" Apagar");
        digitalWrite(led, LOW);
        miBot.endQuery(msg.callbackQueryID, "Led Apagado");
      }
    }
  }

  delay(250);
}
