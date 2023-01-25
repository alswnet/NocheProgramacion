void setup() {
  Serial.begin(115200);

}

void loop() {
  Serial.printf("Memoria Libre %u bytes\n", ESP.getFreeSketchSpace());
  delay(10000);
}
