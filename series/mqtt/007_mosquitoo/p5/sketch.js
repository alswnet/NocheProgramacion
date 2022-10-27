var Opciones = {
  host: "localhost",
  port: 9001,
  protocol: "ws",
  clientId: "CodigoPaginaWeb"
};
var client = mqtt.connect(Opciones);

function EventoConectar() {
  console.log("Conectado a MQTT");
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

console.log("Empezando a conectar");
