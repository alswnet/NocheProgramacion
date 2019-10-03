let BotonActivar;
let BotonApagar;
let EstadoFondo = false;

var client = mqtt.connect('wss://polloALSW:PolloSecreto@broker.shiftr.io', {
  clientId: 'ControladorWeb'
});

function draw() {
  if (EstadoFondo) {
    background(0);
  } else {
    background(255);
  }
}

function setup() {
  createCanvas(200, 200);
  createP();
  BotonActivar = createButton("Activar Led");
  BotonApagar = createButton("Apagar Led");
  BotonActivar.mousePressed(ActivarLed);
  BotonApagar.mousePressed(ApagarLed);
}

function ApagarLed() {
  console.log("Apagnado Led");
  client.publish('/ALSW/Led', '0');
}

function ActivarLed() {
  console.log("Encender Led");
  client.publish('/ALSW/Led', '1');
}


client.on('connect', function() {
  console.log('MQTT conectado');
  client.subscribe('/ALSW/Boton');
});
