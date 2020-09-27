var mqtt = require('mqtt')
const TelegramBot = require('node-telegram-bot-api');

const token = 'xxx';//Pon tu Token aqui
const bot = new TelegramBot(token, {
  polling: true
});

var client = mqtt.connect("mqtt://broker.mqttdashboard.com")

client.on('connect', function() {
  client.subscribe('ALSW/foco1estado');
  client.subscribe('ALSW/foco2estado');
  client.subscribe('ALSW/foco3estado');
  client.subscribe('ALSW/foco4estado');
})

client.on('message', function(topic, message) {
  console.log("Topic " + topic + " - " + message.toString())
})

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  var Mensaje = msg.text;
  console.log("Mensaje " + Mensaje);
  if (Mensaje == "Encender1") {
    client.publish('ALSW/foco1', '1');
    bot.sendMessage(chatId, 'Encendiendo Foco 1');
  } else if (Mensaje == "Apagar1") {
    client.publish('ALSW/foco1', '0');
    bot.sendMessage(chatId, 'Apagar Foco 1');
  } else if (Mensaje == "Encender2") {
    client.publish('ALSW/foco2', '1');
    bot.sendMessage(chatId, 'Encendiendo Foco 2');
  } else if (Mensaje == "Apagar2") {
    client.publish('ALSW/foco2', '0');
    bot.sendMessage(chatId, 'Apagar Foco 2');
  } else if (Mensaje == "Encender3") {
    client.publish('ALSW/foco3', '1');
    bot.sendMessage(chatId, 'Encendiendo Foco 3');
  } else if (Mensaje == "Apagar3") {
    client.publish('ALSW/foco3', '0');
    bot.sendMessage(chatId, 'Apagar Foco 3');
  } else if (Mensaje == "Encender4") {
    client.publish('ALSW/foco4', '1');
    bot.sendMessage(chatId, 'Encendiendo Foco 4');
  } else if (Mensaje == "Apagar4") {
    client.publish('ALSW/foco4', '0');
    bot.sendMessage(chatId, 'Apagar Foco 4');
  } else {
    bot.sendMessage(chatId, 'Comandos Disponibles, Encender1 o Apagar1 (1-4)');
  }
});
