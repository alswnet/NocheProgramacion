/*jshint esversion: 6 */
let BrokerMQTT = 'mqtt://broker.shiftr.io';
let PuertoMQTT = 1883;
let ClienteIDMQTT = "MQTT-Nodejs";
let UsuarioMQTT = "chepecarlos4";
let ContrasenaMQTT = "secretoamor";

const SerialPort = require('serialport');
const port = new SerialPort("/dev/ttyUSB0", {
  baudRate: 9600
});

let Opciones = {
  port: PuertoMQTT,
  clientId: ClienteIDMQTT,
  username: UsuarioMQTT,
  password: ContrasenaMQTT
};

var mqtt = require('mqtt');
var client = mqtt.connect(BrokerMQTT, Opciones);

client.on('connect', function() {
  client.subscribe('/ALSW/Clasificar', function(err) {
    console.log("MQTT Activado");
  });
});

client.on('message', function(topic, message) {
  let Mensaje = message.toString();
  if (Mensaje == "Encender") {
    console.log("Encender Foco");
    port.write("H");
  } else if (Mensaje == "Apagar") {
    console.log("Apagar Foco");
    port.write("L");
  }
});
