var client = mqtt.connect("ws://test.mosquitto.org:8080/mqtt")

function EventoConectar() {
  client.subscribe("ALSW/#", function(err) {
    if (!err) {
      client.publish("ALSW/Temperatura", "30");
    }
  })
}

function EventoMensaje(topic, message) {
  if (topic == "ALSW/temp") {
    console.log("La Temperatura es " + message.toString());
  }
  console.log(topic + " - " + message.toString());
  // client.end()
}

client.on("connect", EventoConectar);
client.on("message", EventoMensaje);
