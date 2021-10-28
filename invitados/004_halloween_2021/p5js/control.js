let BrokerMQTT = "wss://public:public@public.cloud.shiftr.io";
let temaBase = "alsw/posenet";
let clientMQTT;

function setup() {
  noCanvas();
  ConectarMQTT();

  let BotonesExprecions = selectAll(".BotonExprecion");
  for (let B = 0; B < BotonesExprecions.length; B++) {
    BotonesExprecions[B].mousePressed(BotonExprecion);
  }

  let BotonesFondos = selectAll(".BotonFondo");
  for (let B = 0; B < BotonesFondos.length; B++) {
    BotonesFondos[B].mousePressed(BotonFondo);
  }
  
  let BotonesEsqueleto = selectAll(".BotonEsqueleto");
  for (let B = 0; B < BotonesEsqueleto.length; B++) {
    BotonesEsqueleto[B].mousePressed(BotonEsqueleto);
  } 
  
  let BotonesDepuracion = selectAll(".BotonDepuracion");
  for (let B = 0; B < BotonesDepuracion.length; B++) {
    BotonesDepuracion[B].mousePressed(BotonDepuracion);
  }

  let TexBoxBoton = select("#TextBoxColor");
  TexBoxBoton.mousePressed(BotonTextBox);
}

function BotonExprecion() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish(`${temaBase}/exprecion`, NombreBoton);
}

function BotonFondo() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish(`${temaBase}/fondo`, NombreBoton);
}

function BotonEsqueleto() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish(`${temaBase}/esqueleto`, NombreBoton);
}
function BotonDepuracion() {
  var NombreBoton = this.elt.innerText.toLowerCase();
  console.log("Precionado " + NombreBoton);
  clientMQTT.publish(`${temaBase}/depuracion`, NombreBoton);
}

function BotonTextBox() {
  var EtiquetaTextBox = select("#TextBox").value().toLowerCase();
  console.log("Enviando color " + EtiquetaTextBox);
  clientMQTT.publish(`${temaBase}/fondo`, EtiquetaTextBox);
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
