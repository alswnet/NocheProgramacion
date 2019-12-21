const TelegramBot = require('node-telegram-bot-api');
var mqtt = require('mqtt')

const token = '999487663:AAFDUcdqWYPDH_NHC0Gv6cEGXmU84rdq33U'; //Cambiar por el token de telegram
const bot = new TelegramBot(token, {
  polling: true
});
var IdMiChat = 000; //cambiar por tu ID del chat
var client = mqtt.connect('mqtt://NavidadALSW2:SubcribanseAALSWenYoutube@broker.shiftr.io')

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  console.log("El ID del char" + chatId);
  var Mensaje = msg.text.toString().toLocaleLowerCase();
  if (Mensaje.indexOf("encender") >= 0) {
    console.log("encendiendo el led");
    bot.sendMessage(chatId, 'Encendere el led');
    client.publish('/ALSW/foco/Navidad', '1')
  } else if (Mensaje.indexOf("apagar") >= 0) {
    console.log("apagar el led");
    bot.sendMessage(chatId, 'Apagare el led');
    client.publish('/ALSW/foco/Navidad', '1')
  }
});
