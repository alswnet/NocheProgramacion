const OBSWebSocket = require('obs-websocket-js');
var mqtt = require('mqtt');

let BrokerMQTT = 'mqtt://broker.shiftr.io';
let PuertoMQTT = 1883;
let ClienteIDMQTT = "ServidorOBS";
let UsuarioMQTT = "chepecarlos";
let ContrasenaMQTT = "secretoespecial";

let Opciones = {
  port: PuertoMQTT,
  clientId: ClienteIDMQTT,
  username: UsuarioMQTT,
  password: ContrasenaMQTT
}

var client = mqtt.connect(BrokerMQTT, Opciones);

client.on('connect', function() {
  //client.subscribe('/ALSW/Clasificar', function(err) {
  console.log("MQTT Activado")
  //})
})

client.on('message', function(topic, message) {
  let Mensaje = message.toString();
  if (Mensaje == "Encender") {
    console.log("Encender Foco");
    port.write("H");
  } else if (Mensaje == "Apagar") {
    console.log("Apagar Foco")
    port.write("L");
  }
})

let MaquinaOBS = "localhost:4444";
const obs = new OBSWebSocket();

let BuscandoOBS = false;
let FuncionBuscar;

// Intenta Conectar con OBS
ConectnadoOBS();

// Informacion de estado
obs.on('StreamStatus', data => {
  //console.log("Estado Striming");
  //console.log("FPS: " + data.fps);
  //console.log("Striming: " + data.streaming);
  //console.log("Grabacion: " + data.recording);
  console.log("KBS: " + data.kbitsPerSec);
  client.publish('/ALSW/OBS/KBS', ""+data.kbitsPerSec);
})

obs.on('Heartbeat', data => {
  console.log("Info OBS");
  console.log("FPS: " + (data.stats.fps).toFixed(2));
  console.log("Striming: " + data.streaming);
  console.log("Grabacion: " + data.recording);
  console.log("Esena: " + data.currentScene);

  client.publish('/ALSW/OBS/FPS', "" + (data.stats.fps).toFixed(2));
  client.publish('/ALSW/OBS/Streaming', ""+data.streaming);
  client.publish('/ALSW/OBS/Grabacion', ""+data.recording);
})

obs.on('ConnectionClosed', data => {
  console.log("Desactivado obs");
  if (!BuscandoOBS) {
    FuncionBuscar = setInterval(ConectnadoOBS, 5000);
    BuscandoOBS = true;
  }
});

obs.on('ConnectionOpened', data => {
  console.log("Conectando OBS");
  clearInterval(FuncionBuscar);
});

// Error fatal
obs.on('error', err => {
  console.error('socket error:', err);
});


function ConectnadoOBS() {
  console.log("Buscando OBS");
  obs.connect({
      address: MaquinaOBS
    })
    .then(() => {
      console.log("OBS conectado");
      obs.send('SetHeartbeat', {
        'enable': true
      });
      clearInterval(FuncionBuscar);
      BuscandoOBS = false;
    })
    .catch(err => {
      console.log(err);
    });;
}
