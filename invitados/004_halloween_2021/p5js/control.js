let BrokerMQTT = "wss://public:public@public.cloud.shiftr.io";
let clientMQTT
function setup() {
  noCanvas();
  ConectarMQTT();

  BotonesEntrenar = selectAll(".BotoneExprecion");
  for (var B = 0; B < BotonesEntrenar.length; B++) {
    BotonesEntrenar[B].mousePressed(BotoneExprecion);
  }
}

function BotoneExprecion() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish("alsw/posenet/exprecion", NombreBoton);
}

function ConectarMQTT() {
  console.log("Intentando conectar a MQTT");
  clientMQTT = mqtt.connect(BrokerMQTT, {
    clientId: "ALSW_PoseNet" + floor(random(10000)),
  });

  clientMQTT.on("connect", ConectadoMQTT);
  clientMQTT.on("message", RecivirMensaje);
}

function ConectadoMQTT() {
  console.log(`Conectado a MQTT!`);
}

function RecivirMensaje(topic, message) {
  let Mensaje = message
    .toString()
    .toLowerCase()
    .replace(/\r?\n|\r/g, "");
  topic = topic.toString().toLowerCase();
  console.log(`Topic[${topic}]: "${Mensaje}"`);
}
