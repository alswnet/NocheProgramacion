CTBot miBot;

void procesoTelegram(void* pvParameters) {
  while (!estadoWifi.actual) {
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
  while (true) {
    if (estadoWifi.actual) {
      miBot.setTelegramToken(token);
      while (true) {
        loopTelegram();
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void loopTelegram() {
  vTaskDelay(250 / portTICK_PERIOD_MS);

  if (!estadoWifi.actual) {
    estadoBot.actual = false;
    return;
  }

  if (!estadoBot.actual && miBot.testConnection()) {
    estadoBot.actual = true;
  }

  if (estadoBot.actual != estadoBot.anterior) {
    estadoBot.anterior = estadoBot.actual;
    if (estadoBot.actual) {
      Serial.print("TelemanBot: Conectado a ");
      Serial.println(NombreESP);
    } else {
      Serial.println("TelemanBot: Desconectado");
    }
  }

  if (!estadoBot.actual) {
    return;
  }

  TBMessage mensaje;

  if (CTBotMessageText == miBot.getNewMessage(mensaje)) {
    Serial.print("MensajeBot: ");
    Serial.print(mensaje.sender.username);
    Serial.print(" - ");
    Serial.println(mensaje.text);
    miBot.sendMessage(mensaje.sender.id, mensaje.text);
  }
}