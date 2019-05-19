let Camara;
let BotonesEntrenar;
let knn;
let modelo;
let Texto;
let Clasificando = false;
let InputTexbox;
let BotonTexBox;

// Esta informacion se tiene que cambiar dependiendo tu cuenta
// y el Broker MQTT que utilices
let BrokerMQTT = 'broker.shiftr.io';
let PuertoMQTT = 80;
let ClienteIDMQTT = "MQTT-P5";
let UsuarioMQTT = 'chepecarlos';
let ContrasenaMQTT = 'secretoespecial';

client = new Paho.MQTT.Client(BrokerMQTT, PuertoMQTT, ClienteIDMQTT);

client.connect({
  onSuccess: MQTTConectado,
  userName: UsuarioMQTT,
  password: ContrasenaMQTT
});

function MQTTConectado() {
  console.log("MQTT Conectado");
  //client.subscribe("ALSW/foco1estado");
}

client.onConnectionLost = MQTTDesconectado;
client.onMessageArrived = MQTTMensaje;

function MQTTDesconectado(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("Problemas MQTT Desconectado :" + responseObject.errorMessage);
  }
}

function MQTTMensaje(message) {
  console.log("Topic: " + message.destinationName);
  console.log("Mensaje: " + message.payloadString);
}

function setup() {
  createCanvas(320, 240);
  background(255, 0, 0);
  Camara = createCapture(VIDEO);
  Camara.size(320, 240);
  Camara.hide();

  modelo = ml5.featureExtractor('MobileNet', ModeloListo);
  knn = ml5.KNNClassifier();

  createP('Presiona Botones para entrenar');

  let BotonArduino = createButton("Arduino");
  BotonArduino.class("BotonEntrenar");

  let BotonRedboard = createButton("Redboard");
  BotonRedboard.class("BotonEntrenar");

  let BotonESP8266 = createButton("ESP8266");
  BotonESP8266.class("BotonEntrenar");

  let BotonESP32 = createButton("ESP32");
  BotonESP32.class("BotonEntrenar");

  let BotonNada = createButton("Nada");
  BotonNada.class("BotonEntrenar");

  createP("Entrena usando TexBox")

  InputTexbox = createInput("Cosa 2");

  BotonTexBox = createButton("Entrenar con " + InputTexbox.value())
  BotonTexBox.mousePressed(EntrenarTexBox);

  createP("Guarda o Carga tu Neurona");

  let BotonGuardar = createButton("Guardar");
  BotonGuardar.mousePressed(GuardadNeurona);
  let BotonCargar = createButton("Cargar");
  BotonCargar.mousePressed(CargarNeurona);

  Texto = createP("Modelo no Listo, esperando");

  BotonesEntrenar = selectAll(".BotonEntrenar");

  for (let B = 0; B < BotonesEntrenar.length; B++) {
    BotonesEntrenar[B].style("margin", "5px");
    BotonesEntrenar[B].style("padding", "6px");
    BotonesEntrenar[B].mousePressed(PresionandoBoton);
  }
}

function PresionandoBoton() {
  let NombreBoton = this.elt.innerHTML;
  console.log("Entrenando con " + NombreBoton);
  EntrenarKnn(NombreBoton);
}

function EntrenarKnn(ObjetoEntrenar) {
  const Imagen = modelo.infer(Camara);
  knn.addExample(Imagen, ObjetoEntrenar);
}

function ModeloListo() {
  console.log("Modelo Listo");
  Texto.html("Modelo Listo");
}

function clasificar() {
  const Imagen = modelo.infer(Camara);
  knn.classify(Imagen, function(error, result) {
    if (error) {
      console.error();
    } else {
      Texto.html("Es un " + result.label);
      let message = new Paho.MQTT.Message(result.label);
      message.destinationName = "ALSW/ml5/clasificar";
      client.send(message);
      //clasificar();
    }
  })
}

function EntrenarTexBox() {
  const Imagen = modelo.infer(Camara);
  knn.addExample(Imagen, InputTexbox.value());
}

function GuardadNeurona() {
  if (Clasificando) {
    save(knn, "modelo.json");
  }
}

function CargarNeurona() {
  console.log("Cargando una Neurona");
  knn.load("./modelo.json", function() {
    console.log("Neurona Cargada knn");
    Texto.html("Neurona cargana de archivo");
  })
}

function draw() {
  image(Camara, 0, 0, 320, 240);
  BotonTexBox.html("Entrenar con " + InputTexbox.value());
  if (knn.getNumLabels() > 0 && !Clasificando) {
    //clasificar();
    setInterval(clasificar, 500);
    Clasificando = true;
  }
}

// Temporary save code until ml5 version 0.2.2
const save = (knn, name) => {
  const dataset = knn.knnClassifier.getClassifierDataset();
  if (knn.mapStringToIndex.length > 0) {
    Object.keys(dataset).forEach(key => {
      if (knn.mapStringToIndex[key]) {
        dataset[key].label = knn.mapStringToIndex[key];
      }
    });
  }
  const tensors = Object.keys(dataset).map(key => {
    const t = dataset[key];
    if (t) {
      return t.dataSync();
    }
    return null;
  });
  let fileName = 'myKNN.json';
  if (name) {
    fileName = name.endsWith('.json') ? name : `${name}.json`;
  }
  saveFile(fileName, JSON.stringify({
    dataset,
    tensors
  }));
};

const saveFile = (name, data) => {
  const downloadElt = document.createElement('a');
  const blob = new Blob([data], {
    type: 'octet/stream'
  });
  const url = URL.createObjectURL(blob);
  downloadElt.setAttribute('href', url);
  downloadElt.setAttribute('download', name);
  downloadElt.style.display = 'none';
  document.body.appendChild(downloadElt);
  downloadElt.click();
  document.body.removeChild(downloadElt);
  URL.revokeObjectURL(url);
};
