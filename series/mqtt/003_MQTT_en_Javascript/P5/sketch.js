var client = mqtt.connect("ws://test.mosquitto.org:8080/mqtt");
//Si lo usas en hosting para usar encriptado https
// var client = mqtt.connect("wss://test.mosquitto.org:8081/mqtts")

function EventoConectar() {
  client.subscribe("ALSW/#", function(err) {
    if (!err) {
      client.publish("ALSW/Temperatura", "30");
    }
  });
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
