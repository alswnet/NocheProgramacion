let BrokerMQTT = "wss://public:public@public.cloud.shiftr.io";
let TopicBase = ["alsw/posenet/#"];

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
  for (let i = 0; i < TopicBase.length; i++) {
    console.log(`Subcribiendose a ${TopicBase[i]}`);
    clientMQTT.subscribe(TopicBase[i]);
  }
}

function RecivirMensaje(topic, message) {
  let Mensaje = message
    .toString()
    .toLowerCase()
    .replace(/\r?\n|\r/g, "");
  topic = topic.toString().toLowerCase();
  console.log(`Topic[${topic}]: "${Mensaje}"`);
  let ListaTopic = topic.split("/");
  Base = ListaTopic.shift();
  if (Base == "alsw") {
    let Modelo = ListaTopic.shift();
    if (Modelo == "posenet") {
      let Operacion = ListaTopic.shift();
      switch (Operacion) {
        case "fondo":
          if (Mensaje == "camara") {
            EstadoFondo = "camara";
            console.log("Activar camara");
          } else {
            EstadoFondo = "Color";
            EstadoFondoColor = ObtenerColor(Mensaje);
            console.log(`Fondo de color ${EstadoFondoColor}`);
          }
          break;
        case "exprecion":
          for (let i = 0; i < listaExpreciones.length; i++) {
            if (message == listaExpreciones[i]) {
              console.log(`Cambiando exprecion a ${message}`);
              EstadoExprecion = listaExpreciones[i];
              return;
            }
          }
          console.log(`No se encontro expresion a ${message}`);
          break;
        case "depuracion":
          console.log(`Cambiando Depuracion a ${message}`);
          if (Mensaje == "activar") {
            EstadoDepuracio = true;
          } else {
            EstadoDepuracio = false;
          }
          break;
        case "esqueleto":
          console.log(`Cambiando Esqueleto a ${message}`);
          if (Mensaje == "activar") {
            EstadoEsqueleto = true;
          } else {
            EstadoEsqueleto = false;
          }
          break;
      }
    }
  }
}

function ObtenerColor(TextoColor) {
  if (TextoColor === null) {
    return color(0, 255, 255);
    // Color Por Defecto Aqua
  }

  if (TextoColor === "random") {
    let R = floor(random(0, 255));
    let G = floor(random(0, 255));
    let B = floor(random(0, 255));
    let ColorRandon = color(R, G, B);
    console.log(`Color randon ${ColorRandon}`);
    return ColorRandon;
  }

  if (TextoColor in ListaColores) {
    console.log(`Encontrado[${TextoColor}] - ${ListaColores[TextoColor]}`);
    return ListaColores[TextoColor];
  }

  if (ExprecionColores.test(TextoColor)) {
    console.log(`Encontrado[Exprecion Regular]`);
    return color(TextoColor);
  }

  console.log(`No encontrado[Color]`);
  return color(0, 255, 255);
}
