

void procesoWifi(void* pvParameters) {
  estadoWifi.actual = false;
  configurarWifi();
  Serial.println("Entrando Loop Wifi");
  while (true) {
    loopWifi();
  }
}

void configurarWifi() {

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);
  wifiMulti.addAP(ssid_3, password_3);
  WiFi.mode(WIFI_STA);

  Serial.println("Conectando con Wifi...");
  while (wifiMulti.run(1000) != WL_CONNECTED) {
    Serial.print(".");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  if (wifiMulti.run(1000) == WL_CONNECTED) {
    Serial.println("...");
    Serial.println("WiFi Conectado");
    Serial.println("Mi IP es: ");
    Serial.println(WiFi.localIP());
    estadoWifi.actual = true;
  } else {
    estadoWifi.actual = false;
  }

  // MDNS.begin(NombreESP);
  // configurarOTA();

  // MDNS.addService("telnet", "tcp", 23);
  // TelnetStream.begin();
}

void loopWifi() {
  vTaskDelay(50 / portTICK_PERIOD_MS);

  if (wifiMulti.run() != WL_CONNECTED) {
    estadoWifi.actual = false;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  } else {
    estadoWifi.actual = true;
  }

  if (estadoWifi.actual != estadoWifi.anterior) {
    estadoWifi.anterior = estadoWifi.actual;
    if (estadoWifi.actual) {
      Serial.println("WiFi: Conectado");
    } else {
      Serial.println("Wifi: Desconectada");
    }
  }

  // #if defined(ESP8266)
  //     MDNS.update();
  // #endif
  //     ArduinoOTA.handle();
}