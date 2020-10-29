/*jshint esversion: 6 */
const TelegramBot = require('node-telegram-bot-api');

var Contastes = require('./Token');

const bot = new TelegramBot(Contastes.token, {
  polling: true
});

var SerialPort = require('serialport');

var MiPuerto = new SerialPort('/dev/ttyACM0', {
  baudRate: 9600,
  autoOpen: true
});

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  console.log("El ID del char" + chatId);
  var Mensaje = msg.text;
  if (Mensaje == "Temperatura") {
    console.log("Solitando Temperatura");
    bot.sendMessage(chatId, 'Solitando Temperatura');
    MiPuerto.write("T");
  } else if (Mensaje == "Humedad") {
    console.log("Solitando Temperatura");
    bot.sendMessage(chatId, 'Solitando Humedad');
    MiPuerto.write("H");
  } else if (Mensaje == "Calor") {
    console.log("Solitando Temperatura Aparente");
    bot.sendMessage(chatId, 'Solitando Temperatura Aparente');
    MiPuerto.write("C");
  }
});

MiPuerto.setEncoding('utf8');

MiPuerto.on('data', function(data) {
  console.log("Lo que entro es " + data);
  // if (data[0] == 'H') {
//   console.log("Boton Precionado");
//   bot.sendMessage(IdMiChat, "Se preciono el boton");
// }
});
