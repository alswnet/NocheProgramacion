var DivCamara;
var Div
var Camara;
var BotonesEntrenar;
var knn;
var modelo;
var Texto;
var Clasificando = false;
var InputTexbox;
var BotonTexBox;
var BotonCargar;
var BotonSalvar;

let BrokerMQTT = 'broker.shiftr.io';
let PuertoMQTT = 80;
let ClienteIDMQTT = "MQTT-P5";
let UsuarioMQTT = "chepecarlos4";
let ContrasenaMQTT = "secretoamor";

client = new Paho.MQTT.Client(BrokerMQTT, PuertoMQTT, ClienteIDMQTT);

client.onConnectionLost = MQTTPerder;
client.onMessageArrived = MQTTMensaje;

client.connect({
  onSuccess: CuandoConectadoMQTT,
  userName: UsuarioMQTT,
  password: ContrasenaMQTT
});

function MQTTPerder(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("MQTT Perdio coneccion Error:" + responseObject.errorMessage);
  }
}

function MQTTMensaje(message) {
  console.log("Mensaje recibido:" + message.payloadString);
}

function CuandoConectadoMQTT() {
  console.log("MQTT Conectado");
}

function setup() {
  DivCamara = select('#cambas');
  console.log(DivCamara.width);
  Camara = createCapture(VIDEO);
  Camara.size(DivCamara.width, DivCamara.width);
  DivCamara.child(Camara);

  modelo = ml5.featureExtractor('MobileNet', ModeloListo);
  knn = ml5.KNNClassifier();

  InputTexbox = select("#InputText");
  BotonTexBox = select("#BtEntrenar");
  BotonTexBox.mousePressed(EntrenarTexBox);

  BotonGuardar = select("#BtCargar");
  BotonGuardar.mousePressed(GuardadNeurona);
  BotonCargar = select("#BtSalvar");
  BotonCargar.mousePressed(CargarNeurona);

  Texto = select("#EstadoNeurona");
  Texto.html("Neurona: Cargando Modelo");

  BotonesEntrenar = selectAll(".BotonEntrenar");
  for (var B = 0; B < BotonesEntrenar.length; B++) {
    BotonesEntrenar[B].mousePressed(PresionandoBoton);
  }
}

function PresionandoBoton() {
  var NombreBoton = this.elt.value;
  console.log("Entrenando con " + NombreBoton);
  EntrenarKnn(NombreBoton);
}

function EntrenarKnn(ObjetoEntrenar) {
  const Imagen = modelo.infer(Camara);
  knn.addExample(Imagen, ObjetoEntrenar);
}

function ModeloListo() {
  console.log("Modelo Listo");
  Texto.html("Neurona: Modelo Listo");
}

function clasificar() {
  const Imagen = modelo.infer(Camara);
  knn.classify(Imagen, function(error, result) {
    if (error) {
      console.error();
    } else {
      Texto.html("Neurona: Prediccion " + result.label);
      message = new Paho.MQTT.Message(result.label);
      message.destinationName = "ALSW/Clasificar";
      client.send(message);
      //clasificar();
    }
  })
}

function EntrenarTexBox() {
  const Imagen = modelo.infer(Camara);
  console.log("Entenando con " + InputTexbox.value());
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
  if (InputTexbox.value() == "") {
    BotonTexBox.html("Entrenar csson " + InputTexbox.value());
  } else {
    BotonTexBox.html("Entrenar con " + InputTexbox.value());
  }
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
