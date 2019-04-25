var Camara;
var BotonesEntrenar;
var knn;
var modelo;
var Texto;
var Clasificando = false;
var InputTexbox;
var BotonTexBox;

let BrokerMQTT = 'broker.shiftr.io';
let PueroMQTT = 80;
let IDMQTT = 'chepecarlos'
let UsuarioMQTT = 'calorimetria6';
let ContrasenaMQTT = "Calorimetriaweb";


client = new Paho.MQTT.Client(BrokerMQTT, PueroMQTT, IDMQTT);

// connect the client
client.connect({
  onSuccess: ConeccionMQTT,
  userName: UsuarioMQTT,
  password: ContrasenaMQTT
});

function ConeccionMQTT() {
  console.log("conectado MQTT");
  //client.subscribe("musculo0");
}


// set callback handlers
client.onConnectionLost = PerdientoConeccionMQTT;
client.onMessageArrived = MensajeMQTT;


function PerdientoConeccionMQTT(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("PerdientoConeccionMQTT:" + responseObject.errorMessage);
  }
}

Guilexs <guillermolozano169@gmail.com>

8 abr. 2019 22:10

para mí

Traducir mensaje
Desactivar para: inglés
client = new Paho.MQTT.Client('broker.shiftr.io', 80, "Calorimetriaweb");
//var Camara;
var BotonesEntrenar;
var knn;
var modelo;
var Texto;
var Clasificando = false;
var InputTexbox;
var BotonTexBox;
var temperatura = [0, 0, 0, 0, 0, 0];
var m1 = [255, 255];
var m2 = [150, 70];
var m3 = [160, 100];
var m4 = [160, 100];
var m5 = [160, 100];
var m0 = [255, 100];
var dibujito;
var temperaturaminima = 24;
var temperaturamaxima = 30;
var temperaturamedia = (temperaturamaxima - temperaturaminima) / 2;


var canvasdelcuerpo;

function setup() {
  noStroke();
  dibujito = loadImage('cuerohumano.png', 500, 500);
  canvasdelcuerpo = createCanvas(500, 500);
  background(0, 0, 0);
  //Camara = createCapture(VIDEO);
  //Camara.size(320, 240);
  //  Camara.hide();

  modelo = ml5.featureExtractor('MobileNet', ModeloListo);
  knn = ml5.KNNClassifier();

  createP('Presiona Botones para entrenar');

  var BotonArduino = createButton("Feliz");
  BotonArduino.class("BotonEntrenar");

  var BotonRedboard = createButton("Tristeza");
  BotonRedboard.class("BotonEntrenar");

  var BotonESP8266 = createButton("Enojo");
  BotonESP8266.class("BotonEntrenar");


  createP("Entrena usando TexBox")


  InputTexbox = createInput("Cosa 2");

  BotonTexBox = createButton("Entrenar con " + InputTexbox.value())
  BotonTexBox.mousePressed(EntrenarTexBox);

  createP("Guarda o Carga tu Neurona");

  var BotonGuardar = createButton("Guardar");
  BotonGuardar.mousePressed(GuardadNeurona);
  var BotonCargar = createButton("Cargar");
  BotonCargar.mousePressed(CargarNeurona);

  Texto = createP("Modelo no Listo, esperando");


  BotonesEntrenar = selectAll(".BotonEntrenar");

  for (var B = 0; B < BotonesEntrenar.length; B++) {
    BotonesEntrenar[B].style("margin", "5px");
    BotonesEntrenar[B].style("padding", "6px");
    BotonesEntrenar[B].mousePressed(PresionandoBoton);

  }

}

function PresionandoBoton() {
  var NombreBoton = this.elt.innerHTML;
  console.log("Entrenando con " + NombreBoton);
  EntrenarKnn(NombreBoton);
}

function EntrenarKnn(ObjetoEntrenar) {
  const Imagen = modelo.infer(canvasdelcuerpo);
  //  const Imagen = modelo.infer(Camara);//
  knn.addExample(Imagen, ObjetoEntrenar);
}

function ModeloListo() {
  console.log("Modelo Listo");
  Texto.html("Modelo Listo");
}

function clasificar() {
  //const Imagen = modelo.infer(Camara);
  const Imagen = modelo.infer(canvasdelcuerpo);

  knn.classify(Imagen, function(error, result) {
    if (error) {
      console.error();
    } else {
      Texto.html("Es un " + result.label);
      clasificar();
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
let c;

function draw() {
  //image(Camara, 0, 0, 320, 240);
  BotonTexBox.html("Entrenar con " + InputTexbox.value());
  if (knn.getNumLabels() > 0 && !Clasificando) {
    clasificar();
    Clasificando = true;
  }
  //  fill(100, 100, 0);
  //console.log(temperatura[0]);
  c = TemperaturaDibujo(temperatura[0]);
  fill(c);
  ellipse(240, 100, 50, 50);
  c = TemperaturaDibujo(temperatura[1]);
  fill(c);
  ellipse(255, 255, 50, 50);
  c = TemperaturaDibujo(temperatura[2]);
  fill(c);
  ellipse(260, 400,30, 30);


  TemperaturaDibujo(temperatura[1]);
  ellipse(m2[0], m2[1], 50, 50);
  ellipse(m3[0], m3[1], 50, 50);
  ellipse(m4[0], m4[1], 50, 50);
  ellipse(m5[0], m5[1], 50, 50);

image(dibujito, 0, 0)
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
// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({
  onSuccess: onConnect,
  userName: 'calorimetria6',
  password: 'contrasena'
});


// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("conectado MQTT");
  client.subscribe("musculo0");
  client.subscribe("musculo1");
  client.subscribe("musculo2");
  client.subscribe("musculo3");
  client.subscribe("musculo4");
  client.subscribe("musculo5");
  //  message = new Paho.MQTT.Message("Hello");
  //  message.destinationName = "World";
  //  client.send(message);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:" + responseObject.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {

  console.log("onMessageArrived:" + message.payloadString);
  console.log("titulo" + message.destinationName);

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

  var BotonArduino = createButton("Arduino");
  BotonArduino.class("BotonEntrenar");

  var BotonRedboard = createButton("Redboard");
  BotonRedboard.class("BotonEntrenar");

  var BotonESP8266 = createButton("ESP8266");
  BotonESP8266.class("BotonEntrenar");

  var BotonESP32 = createButton("ESP32");
  BotonESP32.class("BotonEntrenar");

  var BotonNada = createButton("Nada");
  BotonNada.class("BotonEntrenar");

  createP("Entrena usando TexBox")


  InputTexbox = createInput("Cosa 2");

  BotonTexBox = createButton("Entrenar con " + InputTexbox.value())
  BotonTexBox.mousePressed(EntrenarTexBox);

  createP("Guarda o Carga tu Neurona");

  var BotonGuardar = createButton("Guardar");
  BotonGuardar.mousePressed(GuardadNeurona);
  var BotonCargar = createButton("Cargar");
  BotonCargar.mousePressed(CargarNeurona);

  Texto = createP("Modelo no Listo, esperando");


  BotonesEntrenar = selectAll(".BotonEntrenar");

  for (var B = 0; B < BotonesEntrenar.length; B++) {
    BotonesEntrenar[B].style("margin", "5px");
    BotonesEntrenar[B].style("padding", "6px");
    BotonesEntrenar[B].mousePressed(PresionandoBoton);

  }

}

function PresionandoBoton() {
  var NombreBoton = this.elt.innerHTML;
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
      clasificar();
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
    clasificar();
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
