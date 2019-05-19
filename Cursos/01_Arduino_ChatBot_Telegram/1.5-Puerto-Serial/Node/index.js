const TelegramBot = require('node-telegram-bot-api');

const token = 'xxx';//Cambiar por el token de telegram
const bot = new TelegramBot(token, {
  polling: true
});
var IdMiChat = 000;//cambiar por tu ID del chat

var SerialPort = require('serialport');
var MiPuerto = new SerialPort('/dev/ttyUSB0', {
  baudRate: 9600,
  autoOpen: true
});

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  console.log("El ID del char" + chatId);
  var Mensaje = msg.text;
  if (Mensaje == "Encender") {
    console.log("encendiendo el led");
    bot.sendMessage(chatId, 'Encendere el led');
    MiPuerto.write("H");
  } else if (Mensaje == "Apagar") {
    console.log("apagar el led");
    bot.sendMessage(chatId, 'Apagare el led');
    MiPuerto.write("L");
  }
});

MiPuerto.setEncoding('utf8');

MiPuerto.on('data', function(data) {
  console.log("Lo que entro es " + data);
  if (data[0] == 'H') {
    console.log("Boton Precionado");
    bot.sendMessage(IdMiChat, "Se preciono el boton");
  }
});
