let BrokerMQTT = "wss://public:public@public.cloud.shiftr.io";
let clientMQTT;
let temaBasel = "alsw/posenet";

function setup() {
  noCanvas();
  ConectarMQTT();

  let BotonesExprecions = selectAll(".BotoneExprecion");
  for (let B = 0; B < BotonesExprecions.length; B++) {
    BotonesExprecions[B].mousePressed(BotoneExprecion);
  }

  let BotonesFondos = selectAll(".BotoneFondo");
  for (let B = 0; B < BotonesFondos.length; B++) {
    BotonesFondos[B].mousePressed(BotoneFondo);
  }
  
  let BotonesEsqueleto = selectAll(".BotoneEsqueleto");
  for (let B = 0; B < BotonesEsqueleto.length; B++) {
    BotonesEsqueleto[B].mousePressed(BotoneEsqueleto);
  } 
  
  let BotonesDepuracion = selectAll(".BotoneDepuracion");
  for (let B = 0; B < BotonesDepuracion.length; B++) {
    BotonesDepuracion[B].mousePressed(BotoneDepuracion);
  }

  let TexBoxBoton = select("#TextBoxColor");
  TexBoxBoton.mousePressed(BotonTextBox);
}

function BotoneExprecion() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish(`${temaBasel}/exprecion`, NombreBoton);
}

function BotoneFondo() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish(`${temaBasel}/fondo`, NombreBoton);
}

function BotoneEsqueleto() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish(`${temaBasel}/esqueleto`, NombreBoton);
}
function BotoneDepuracion() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish(`${temaBasel}/depuracion`, NombreBoton);
}

function BotonTextBox() {
  var EtiquetaTextBox = select("#TextBox").value().toLowerCase();
  console.log("Enviando color " + EtiquetaTextBox);
  clientMQTT.publish(`${temaBasel}/fondo`, EtiquetaTextBox);
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
