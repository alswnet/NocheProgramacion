/*jshint esversion: 6 */
var NodeWebcam = require("node-webcam");
const TelegramBot = require("node-telegram-bot-api");

var opts = {
  width: 1280,
  height: 720,
  quality: 100,
  delay: 0,
  saveShots: true,
  output: "jpeg",
  device: "/dev/video1",
  callbackReturn: "location",
  verbose: true
};

var Webcam = NodeWebcam.create(opts);

const token = "";

const bot = new TelegramBot(token, {
  polling: true
});

Webcam.list(function(list) {
  console.log(list);
});

bot.on("message", msg => {
  const chatId = msg.chat.id;
  bot.sendMessage(chatId, "Tomando Foto");
  Webcam.capture("Foto", function(err, data) {
    bot.sendPhoto(chatId, "Foto.jpg", {
      caption: "Foto Oculta"
    });
    console.log("Foto Enviada");
  });
});
