const TelegramBot = require('node-telegram-bot-api');
const token = 'XXX';//Token de Github
const bot = new TelegramBot(token, {
  polling: true
});

var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://broker.mqttdashboard.com')

var IdSecreto = 1234567;

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  console.log("El charid es " + chatId);
  bot.sendMessage(chatId, 'Received your message');
});

client.on('connect', function() {
  client.subscribe('ALSWcalabasa', function(err) {})
})

client.on('message', function(topic, message) {
  bot.sendMessage(IdSecreto, 'Mi amo alquien llego ' + message.toString());
  console.log(message.toString())
})
