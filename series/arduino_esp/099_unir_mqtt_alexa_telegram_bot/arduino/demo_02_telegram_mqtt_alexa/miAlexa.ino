Espalexa miAlexa;

void procesoAlexa(void *pvParameters) {
  estadoAlexa.actual = false;
  while (!estadoWifi.actual) {
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
  configurarAlexa();
  Serial.println("Entrando Loop Alexa");
  while (true) {
    loopAlexa();
  }
}

void configurarAlexa() {
  miAlexa.addDevice("pollo", mensajeAlexa);
  miAlexa.begin();
}

void loopAlexa() {
  vTaskDelay(100 / portTICK_PERIOD_MS);

  if (!estadoWifi.actual) {
    estadoBot.actual = false;
    return;
  }

  miAlexa.loop();
  delay(10);
}

void mensajeAlexa(uint8_t brillo) {
  Serial.print("MensajeAlexa: ");
  Serial.println(brillo);
}