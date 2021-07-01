// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

var mqtt = require("mqtt");
// var client = mqtt.connect("mqtt://test.mosquitto.org");

var Opciones = {
  host: "localhost",
  port: 1883,
  protocol: "mqtt",
  clientId: "YoCodigo1"
};
var client = mqtt.connect(Opciones);

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
