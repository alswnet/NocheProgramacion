/*jshint esversion: 6 */
const TelegramBot = require("node-telegram-bot-api");

var Contastes = require("./Token");

const bot = new TelegramBot(Contastes.token, {
  polling: true
});

var SerialPort = require("serialport");
const Readline = require("@serialport/parser-readline");
var MiPuerto = new SerialPort("/dev/ttyACM0", {
  baudRate: 9600,
  autoOpen: true
});
const MiParse = new Readline();
MiPuerto.pipe(MiParse);

var Cliente = 123;

bot.on("message", msg => {
  const chatId = msg.chat.id;
  Cliente = chatId;
  var Mensaje = msg.text;
  console.log("El ID del char: " + chatId + " Usuario: " + msg.chat.first_name + " con  el mensaje: " + Mensaje);
  if (Mensaje == "Temperatura" || Mensaje == "T" || Mensaje == "t") {
    console.log("Pidiendo la Temperatura");
    bot.sendMessage(chatId, "Pidiendo la temperatura");
    MiPuerto.write("t");
  } else if (Mensaje == "Humedad" || Mensaje == "H" || Mensaje == "h") {
    console.log("Pidiendo la Humedad");
    bot.sendMessage(chatId, "Pidiendo la Humedad");
    MiPuerto.write("h");
  } else if (Mensaje == "Aparente" || Mensaje == "A" || Mensaje == "a") {
    console.log("Pidiendo la Temperatura Aparente");
    bot.sendMessage(chatId, "Pidiendo la Temperatura Aparente");
    MiPuerto.write("a");
  } else {
    bot.sendMessage(chatId, "No entiendo el mensaje");
  }
});

MiParse.setEncoding("utf8");

MiParse.on("data", function(data) {
  console.log("Lo que entro es " + data);
  var Mensaje = data.split(";");
  if (Mensaje[0] == "T") {
    bot.sendMessage(Cliente, "La temperatura es " + Mensaje[1] + "°C");
  } else if (Mensaje[0] == "H") {
    bot.sendMessage(Cliente, "La Humedad es " + Mensaje[1] + "%");
  } else if (Mensaje[0] == "A") {
    bot.sendMessage(Cliente, "La Temperatura Aparente es " + Mensaje[1] + "°C");
  }
});
