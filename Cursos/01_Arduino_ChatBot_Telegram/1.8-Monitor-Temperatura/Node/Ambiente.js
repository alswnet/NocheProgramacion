/*jshint esversion: 6 */
const TelegramBot = require('node-telegram-bot-api');

var Contastes = require('./Token');

const bot = new TelegramBot(Contastes.token, {
  polling: true
});

var SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const MiPuertoParse = new Readline();

var MiPuerto = new SerialPort('/dev/ttyACM0', {
  baudRate: 9600,
  autoOpen: true
});
MiPuerto.pipe(MiPuertoParse);
var chatId;

bot.on('message', (msg) => {
  chatId = msg.chat.id;
  console.log("El ID del char " + chatId);
  var Mensaje = msg.text;
  if (Mensaje == "Temperatura" || Mensaje == "T") {
    console.log("Solitando Temperatura");
    bot.sendMessage(chatId, 'Solitando Temperatura');
    MiPuerto.write("T");
  } else if (Mensaje == "Humedad" || Mensaje == "H") {
    console.log("Solitando Temperatura");
    bot.sendMessage(chatId, 'Solitando Humedad');
    MiPuerto.write("H");
  } else if (Mensaje == "Aparente" || Mensaje == "A") {
    console.log("Solitando Temperatura Aparente");
    bot.sendMessage(chatId, 'Solitando Temperatura Aparente');
    MiPuerto.write("C");
  }
});

MiPuerto.setEncoding('utf8');

MiPuertoParse.on('data', function(data) {
  var Mensaje = data.split(";");
  if (Mensaje[0] == 'T') {
    console.log("Enviando Temperatura");
    bot.sendMessage(chatId, "Temperatura es " + Mensaje[1] + "°C");
  } else if (Mensaje[0] == 'H') {
    console.log("Enviando Humedad");
    bot.sendMessage(chatId, "Humedad es " + Mensaje[1] + "%");
  } else if (Mensaje[0] == 'A') {
    console.log("Enviando Humedad");
    bot.sendMessage(chatId, "Temperatura Aparente es " + Mensaje[1] + "°C");
  }
});
