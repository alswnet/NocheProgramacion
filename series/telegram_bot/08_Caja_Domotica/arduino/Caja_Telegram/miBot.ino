#include "CTBot.h"
#include "Utilities.h"

CTBot miBot;
CTBotInlineKeyboard miTeclado;
boolean bienbenidaBot = false;

void configurarBot() {
  miBot.setTelegramToken(token);

  for (int i = 0; i < CantidadAparatos; i++) {
    miTeclado.addButton(Aparatos[i].nombre, Aparatos[i].nombre, CTBotKeyboardButtonQuery);
    if (i % 3 == 0) {
      miTeclado.addRow();
    }
  }
}

void mensajeBienbenidaBot() {
  if (!bienbenidaBot) {
    bienbenidaBot = true;
    Serial << "En Linea, Sistema: " << nombre << "\n";
    for (int i = 0; i < cantidadChats; i++) {
      miBot.sendMessage(IDchat[i], "En Linea, Sistema: " + String(nombre));
    }
  }

  if (estado < conectado) {
    bienbenidaBot = false;
  }
}

void actualizarBot() {
  if (estado != conectado) {
    return;
  }

  mensajeBienbenidaBot();

  TBMessage msg;

  if (miBot.getNewMessage(msg)) {
    Serial.println();
    TelnetStream.println();
    Serial << "Mensaje: " << msg.text << " de " << msg.sender.username << " ID:" << msg.sender.id << "\n";
    TelnetStream << "Mensaje: " << msg.text << " de " << msg.sender.username << " ID:" << msg.sender.id << "\n";
    for (int i = 0; i < cantidadChats; i++) {
      if (msg.sender.id == IDchat[i]) {
        if (msg.messageType == CTBotMessageQuery) {
          for (int i = 0; i < CantidadAparatos; i++) {
            if (msg.callbackQueryData.equals(Aparatos[i].nombre)) {
              Serial.println("Cambio por Teclado");
              TelnetStream.println("Cambio por Teclado");
              Aparatos[i].Estado = !Aparatos[i].Estado;
              String Mensaje = "Aparato ";
              Mensaje += Aparatos[i].nombre;
              Mensaje += ": ";
              Mensaje += (Aparatos[i].Estado ? "Encendido" : "Apagado");
              TelnetStream.println(Mensaje);
              Serial.println(Mensaje);
              miBot.endQuery(msg.callbackQueryID, Mensaje);
              return;
            }
          }
        } else if (msg.text.equalsIgnoreCase("estado")) {
          Serial.println("Enviando estado");
          TelnetStream.println("Enviando estado");
          PedirEstado(msg.sender.id);
        } else if (msg.text.equalsIgnoreCase("opciones")) {
          Serial.println("Enviando opciones");
          TelnetStream.println("Enviando opciones");
          PedirEstado(msg.sender.id);
          miBot.sendMessage(msg.sender.id, "Cambiar", miTeclado);
        } else if (msg.text.equalsIgnoreCase("encender") || msg.text.equalsIgnoreCase("e")) {
          Serial.println("Encendiendo todo");
          TelnetStream.println("Encendiendo todo");
          for (int i = 0; i < CantidadAparatos; i++) {
            Aparatos[i].Estado = true;
          }
          miBot.sendMessage(msg.sender.id, "Encendiendo todos los aparatos");
        } else if (msg.text.equalsIgnoreCase("apagar") || msg.text.equalsIgnoreCase("a")) {
          Serial.println("Apagar todo");
          TelnetStream.println("Apagar todo");
          for (int i = 0; i < CantidadAparatos; i++) {
            Aparatos[i].Estado = false;
          }
          miBot.sendMessage(msg.sender.id, "Apagando todos los aparatos");
        } else if (msg.text.equalsIgnoreCase("cambiar") || msg.text.equalsIgnoreCase("c")) {
          Serial.println("Cambia todo");
          TelnetStream.println("Cambia todo");
          for (int i = 0; i < CantidadAparatos; i++) {
            Aparatos[i].Estado = !Aparatos[i].Estado;
          }
          miBot.sendMessage(msg.sender.id, "Cambiando todos los aparatos");
        } else if (msg.text.equalsIgnoreCase("formatiar si si")) {
          Serial.println("Formatiar LittleFS");
          TelnetStream.println("Formatiar LittleFS");
          formatiarMemoria(Serial);
          miBot.sendMessage(msg.sender.id, "Borrando todo la memoria y inicializandola");
        } else {
          for (int i = 0; i < CantidadAparatos; i++) {
            if (msg.text.equalsIgnoreCase(Aparatos[i].nombre)) {
              Serial.println("Cambio por Nombre");
              TelnetStream.println("Cambio por Nombre");
              Aparatos[i].Estado = !Aparatos[i].Estado;
              String Mensaje = "Cambiando ";
              Mensaje += Aparatos[i].nombre;
              Mensaje += ": ";
              Mensaje += (Aparatos[i].Estado ? "encendido" : "apagado");
              Serial.println(Mensaje);
              TelnetStream.println(Mensaje);
              miBot.sendMessage(msg.sender.id, Mensaje);
              return;
            }
          }
          Serial.println("Enviar 'opciones'");
          TelnetStream.println("Enviar 'opciones'");
          miBot.sendMessage(msg.sender.id, "Prueba 'opciones'");
        }
        return;
      }
    }

    Serial << "Usuario no reconocido\n";
    Serial << "Nombre: " << msg.sender.firstName << " - " << msg.sender.lastName << "\n";
    Serial << "Usuario: " << msg.sender.username << " ID: " << int64ToAscii(msg.sender.id) << "\n";

    TelnetStream << "Usuario no reconocido\n";
    TelnetStream << "Nombre: " << msg.sender.firstName << " - " << msg.sender.lastName << "\n";
    TelnetStream << "Usuario: " << msg.sender.username << " ID: " << int64ToAscii(msg.sender.id) << "\n";

    miBot.sendMessage(msg.sender.id, "No te conosco, lo siento habla con mi amo");
  }
}

void PedirEstado(int64_t IDchat) {
  String Mensaje = "Estado actual\n";

  for (int i = 0; i < CantidadAparatos; i++) {
    Mensaje += "Aparato ";
    Mensaje += Aparatos[i].nombre;
    Mensaje += ": ";
    Mensaje += (Aparatos[i].Estado ? "Encencido" : "Apagado");
    Mensaje += "\n";
  }

  TelnetStream.println(Mensaje);
  Serial.println(Mensaje);
  miBot.sendMessage(IDchat, Mensaje);
}