WiFiClient netMQTT;
MQTTClient clientMQTT;

unsigned long lastMillis = 0;

void procesoMQTT(void *pvParameters) {
  estadoMQTT.actual = false;
  while (!estadoWifi.actual) {
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
  configurarMQTT();
  Serial.println("Entrando Loop MQTT");
  while (true) {
    loopMQTT();
  }
}

void configurarMQTT() {
  clientMQTT.begin(BrokerMQTT, netMQTT);
  clientMQTT.onMessage(mensajeMQTT);
  clientMQTT.subscribe(TopicMQTT);
}

void mensajeMQTT(String &topic, String &payload) {
  Serial.println("MensajeMQTT: " + topic + " - " + payload);
}

void loopMQTT() {
  vTaskDelay(100 / portTICK_PERIOD_MS);

  if (!estadoWifi.actual) {
    estadoMQTT.actual = false;
    return;
  }

  clientMQTT.loop();
  delay(10);

  if (clientMQTT.connected()) {
    estadoMQTT.actual = true;
  } else {
    estadoMQTT.actual = false;
    if (!clientMQTT.connect(NombreESP)) {
      vTaskDelay(500 / portTICK_PERIOD_MS);
      Serial.println("MQTT - No Conectada!");
      return;
    } else {
      clientMQTT.subscribe(TopicMQTT);
    }
  }

  if (estadoMQTT.actual != estadoMQTT.anterior) {
    estadoMQTT.anterior = estadoMQTT.actual;
    if (estadoMQTT.actual) {
      clientMQTT.subscribe(TopicMQTT);
      Serial.print("MQTT: Conectado a ");
      Serial.println(BrokerMQTT);
    } else {
      Serial.println("MQTT: Desconectado");
    }
  }

  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    clientMQTT.publish("/hello", "world");
  }
}