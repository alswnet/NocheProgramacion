import mqtt.*;

MQTTClient client;

void setup() {
  client = new MQTTClient(this);
  client.connect("mqtt://test.mosquitto.org", "processing_" + random(0, 1000) );
  println("Esperado conectar a MQTT");
}

void draw() {
}

void keyPressed() {
  String Tecla = String.valueOf(key);
  println("Mensaje "+ Tecla);
  client.publish("/ALSW/processing", Tecla);

}

void clientConnected() {
  println("Conectado a MQTT");
  client.subscribe("/ALSW/#");
}

void messageReceived(String topic, byte[] payload) {
  println("Nuevo Mensaje MQTT " + topic + " - " + new String(payload));
}

void connectionLost() {
  println("Desconectado MQTT");
}
