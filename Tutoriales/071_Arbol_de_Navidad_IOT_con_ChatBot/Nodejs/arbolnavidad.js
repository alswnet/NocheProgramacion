/*jshint esversion: 6 */
var Contastes = require('./Token');

const TelegramBot = require('node-telegram-bot-api');
const fs = require('fs');
const NodeWebcam = require("node-webcam");
var Jimp = require('jimp');

var SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
var MiPuerto = new SerialPort(Contastes.puertoserial, {
  baudRate: 9600,
  autoOpen: true
});
const MiParse = new Readline();
MiPuerto.pipe(MiParse);

const bot = new TelegramBot(Contastes.telegram_token, {
  polling: true
});


var opts = {
  width: 1280,
  height: 720,
  quality: 100,
  delay: 2,
  saveShots: true,
  output: "jpeg",
  device: Contastes.camara,
  callbackReturn: "location",
  verbose: true
};

var Webcam = NodeWebcam.create(opts);

Webcam.list(function(list) {
  console.log("Lista de camaras disponible:")
  console.log(list);
});


console.log("Arbol de Navidad 2020");

bot.on('message', (msg) => {
  if (msg.from.is_bot) {
    console.log("Es un Bot");
  } else {
    // SalvarChat(msg);
    var chatId = msg.chat.id;
    var Mensaje = msg.text.toLowerCase();

    if (chatId == Contastes.chatidadmin) {
      if (EstaTexto(Mensaje, "depuracion") || Mensaje == "/\depuracion") {
        console.log("Cambiando modo depuracion");
        MensajeDepuracion();
      }
    }

    if (EstaTexto(Mensaje, "foto") || Mensaje == "/\foto") {
      console.log("Preperando tomar foto");
      MensajeFoto(chatId, msg.date);
    } else if (EstaTexto(Mensaje, "estado") || Mensaje == "/\estado") {
      console.log("Pidiendo estado");
      MensajeEstado(chatId);
    } else if (EstaTexto(Mensaje, "listacolor") || Mensaje == "/\listacolor") {
      console.log("Mandando Lista de colores");
      MensajeListaColor(chatId);
    } else if (EstaTexto(Mensaje, "matris") || Mensaje == "/\matris") {
      console.log("Cambiando a color matris");
      SalvarUltimo(msg);
      CambiarColorMatrix(chatId, Mensaje);
    } else if (EstaTexto(Mensaje, "color") || Mensaje == "/\color") {
      console.log("Cambiando a color");
      SalvarUltimo(msg);
      CambiarColor(chatId, Mensaje);
    } else if (EstaTexto(Mensaje, "ayuda") || Mensaje == "/\ayuda") {
      MensajeAyuda(chatId)
    } else if (EstaTexto(Mensaje, "inicio") || Mensaje == "/\start") {
      MensajeBienbenida(chatId);
    } else if (EstaTexto(Mensaje, "codigo") || Mensaje == "/\codigo") {
      bot.sendMessage(chatId, 'Codigo fuente: https://github.com/alswnet/ArbolNavidad2020');
    } else if (EstaTexto(Mensaje, "web") || Mensaje == "/\web") {
      bot.sendMessage(chatId, 'Pagina web del proyecto: https://nocheprogramacion.com/arbolnavidad');
    } else if (EstaTexto(Mensaje, "video") || Mensaje == "/\video") {
      bot.sendMessage(chatId, 'Video proyecto: https://youtube.com/alswnet');
    } else if (EstaTexto(Mensaje, "error") || Mensaje == "/\error") {
      bot.sendMessage(chatId, 'Reporar Errores o problemas o ideas en: https://github.com/alswnet/ArbolNavidad2020/issues');
    } else if (EstaTexto(Mensaje, "discord") || Mensaje == "/\discord") {
      bot.sendMessage(chatId, 'Discord: https://nocheprogramacion.com/discord');
    } else if (EstaTexto(Mensaje, "nocheprogramacion") || Mensaje == "tutorial" || Mensaje == "\/tutorial") {
      bot.sendMessage(chatId, 'Tutoriales: https://nocheprogramacion.com');
    } else if (EstaTexto(Mensaje, "programacionnews") || EstaTexto(Mensaje, "noticias") || Mensaje == "\/noticias") {
      bot.sendMessage(chatId, 'Noticas: https://programacion.news');
    } else {
      bot.sendMessage(chatId, 'No entiendo intenta con /ayuda o entra a https://nocheprogramacion.com/arbolnavidad');
    }
  }
});


function SalvarUltimo(Mensaje) {
  var Nombre = Mensaje.chat.first_name;
  var Fecha = FechaActual();
  var Texto = Mensaje.text;
  var data = {
    'Nombre': Nombre,
    'Fecha': Fecha,
    'mensaje': Texto
  }

  data = JSON.stringify(data);
  fs.writeFileSync('Data/Ultimo.json', data);
}

function SalvarChat(Mensaje) {
  var ID = Mensaje.chat.id
  var User = Mensaje.chat.username;
  var Lenguaje = Mensaje.language_code;
  var Nombre = Mensaje.chat.first_name;
  var Fecha = new Date(Mensaje.date * 1000);
  var Texto = Mensaje.text;
  var Salvar = {
    'ID': ID,
    'User': User,
    'Nombre': Nombre,
    'Fecha': Fecha,
    'Texto': Texto,
    'Lenguaje': Lenguaje
  }

  fs.readFile('./Data/Historia.json', function(err, data) {
    var json = JSON.parse(data);
    json.Historia.push(Salvar);
    fs.writeFile("./Data/Historia.json", JSON.stringify(json),
      function(err) {
        if (err) throw err;
        console.log('The data was appended to file!');
      });
  });
}

function EstaTexto(Mensaje, Texto) {
  if (Mensaje.indexOf(Texto) >= 0) {
    return true;
  } else {
    return false;
  }
}

function MensajeBienbenida(ID) {
  var Mensaje = "*Bienbenido* al Bot del Arbol de Navidad 2020 *ALSW* \n";
  Mensaje += "Si es tu primera vez por aqui entra a: \n";
  Mensaje += "https://nocheprogramacion.com/arbolnavidad \n";
  Mensaje += "o usa el comando \n";
  Mensaje += "/ayuda \n";
  Mensaje += "*Feliz Navidad de ALSW*";

  bot.sendMessage(ID, Mensaje, {
    parse_mode: "Markdown"
  });
}

function ListaColor() {
  let ArchivoColores = fs.readFileSync('Colores.json');
  let Colores = JSON.parse(ArchivoColores)['Colores'];
  return Colores;
}

function MensajeListaColor(ID) {
  Colores = ListaColor();
  var Mensaje = "Lista de *colores* disponibles:\n"
  Colores.forEach((Color, i) => {
    Mensaje += Color + "\n"
  });
  Mensaje += "*Ejemplo:*\n";
  Mensaje += "/color rojo";

  bot.sendMessage(ID, Mensaje, {
    parse_mode: "Markdown"
  });
}

function CambiarColorMatrix(ID, Mensaje) {
  Colores = ListaColor();
  MensajeColores = [];
  var TextoColor = "";
  ParteMensaje = Mensaje.split(' ');
  console.log(ParteMensaje)
  if (ParteMensaje.length > 1) {
    console.log("Empezando a procesar")
    for (var i = 1; i < ParteMensaje.length; i++) {
      Colores.forEach((Color, j) => {
        if (EstaTexto(ParteMensaje[i], Color)) {
          MensajeColores.push(Color);
        }
      });
    }
  }


  if (MensajeColores.length > 0) {
    console.log("Enviando " + MensajeColores);
    TextoColor += "Se envio " + MensajeColores;
    MensajeMatrix(MensajeColores);
  } else {
    console.log("No suficiente valores");
    TextoColor += "Lista de Color no esta en la lista intenta /listacolor"
  }

  bot.sendMessage(ID, TextoColor, {
    parse_mode: "Markdown"
  });
}

function CambiarColor(ID, Mensaje) {

  Colores = ListaColor();
  var Encontrado = false;
  console.log(Mensaje, Colores.length)

  for (var i = 0; i < Colores.length; i++) {
    console.log(i, Mensaje, Colores[i]);
    if (EstaTexto(Mensaje, Colores[i])) {
      console.log("Color encontrado: " + Colores[i])
      var TextoColor = "";
      if (MensajeSerial(Colores[i])) {
        TextoColor += "Cambiando el arbol a color:\n*";
        TextoColor += Colores[i] + "*";
      } else {
        TextoColor += "Error con el Arduino";
      }
      bot.sendMessage(ID, TextoColor, {
        parse_mode: "Markdown"
      });
      Encontrado = true;
      return;
    }
  }
  if (!Encontrado) {
    bot.sendMessage(ID, 'Color no esta en la lista intenta /listacolor');
  }

}

function MensajeMatrix(colores) {
  MiPuerto.write("matris/reiniciar*");
  for (var i = 0; i < colores.length; i++) {
    MiPuerto.write("matris/" + colores[i] + "*");
  }
  MiPuerto.write("matris/activar*");
  return true;
}

function MensajeSerial(Color) {
  MiPuerto.write("color/" + Color + "*");
  return true;
}

function MensajeFoto(ID, Tiempo) {
  var Mensaje = "Tomando *FOTO* espera\n";
  Mensaje += "Recuerda compartir y etiquetarnos como @ALSWnet";
  bot.sendMessage(ID, Mensaje, {
    parse_mode: "Markdown"
  });
  var NombreImagen = "./Foto/" + ID + "-" + Tiempo + ".jpg";
  Webcam.capture(NombreImagen, function(err, data) {
    if (err) {
      console.log("Error con la camara");
      bot.sendMessage(ID, 'Error con la camara, disculpa :( ');
    } else {
      EditandoImagen(ID, NombreImagen);
      console.log("Foto Enviada " + NombreImagen);
    }
  });
}

async function EditandoImagen(ID, NombreImagen) {
  console.log("EditandoImagen")
  let ImagenBase = await Jimp.read(NombreImagen);
  let Ultimo = fs.readFileSync('Data/Ultimo.json');
  Ultimo = JSON.parse(Ultimo);
  let ImagenExtra = await Jimp.read("./Foto/Mascara.png")
  var Fuente = await Jimp.loadFont(Jimp.FONT_SANS_32_WHITE);
  await ImagenBase.resize(1080, Jimp.AUTO);
  ImagenExtra.composite(ImagenBase, 100, 120, {
    mode: Jimp.BLEND_DESTINATION_OVER,
    opacityDest: 1,
    opacitySource: 1
  })
  ImagenExtra.print(Fuente, 180, 655, "Nombre: " + Ultimo['Nombre'], 600);
  ImagenExtra.print(Fuente, 180, 690, "Fecha: " + Ultimo['Fecha'], 600);

  await ImagenExtra.writeAsync(NombreImagen);

  bot.sendPhoto(ID, NombreImagen, {
    caption: "Arbol configurado por " + Ultimo['Nombre'] + " a " + Ultimo['Fecha']
  });
}

function FechaActual() {
  var anno = (new Date()).getFullYear();
  var mes = (new Date()).getMonth() + 1;
  var dia = (new Date()).getDate();
  var hora = (new Date()).getHours();
  if (hora < 10) {
    hora = "0" + hora;
  }
  var minuto = (new Date()).getMinutes();
  if (minuto < 10) {
    minuto = "0" + minuto;
  }
  return hora + ":" + minuto + " " + dia + "/" + mes + "/" + anno
}


function MensajeEstado(ID) {
  let Ultimo = fs.readFileSync('Data/Ultimo.json');
  Ultimo = JSON.parse(Ultimo);
  var Mensaje = "Ultima configuracion por: " + Ultimo['Nombre'] + "\n";
  Mensaje += "Hora y Fecha: " + Ultimo['Fecha'] + "\n";
  Mensaje += "Mensaje: " + Ultimo['mensaje'] + "\n";
  Mensaje += "Puede tomarle foto con /foto";
  bot.sendMessage(ID, Mensaje, {
    parse_mode: "Markdown"
  });
}

function MensajeAyuda(ID) {
  var Mensaje = "El *Bot* tiene los siquientes comandos:\n"
  Mensaje += "/start  Mensaje de Bienbenida del Bot\n";
  Mensaje += "/estado Devuelve estado actual del arbol colores y usuario\n"
  Mensaje += "/foto Pedir foto del arbol actual\n";
  Mensaje += "/color {COLOR} Cambiar el color de arbol a un color de la lista\n";
  Mensaje += "/matris {Color} {Color} ... {Color} Cambia el arbol en base a una secuencia de colores"
  Mensaje += "/listacolor Muestra lista de colores para el arbol\n";
  Mensaje += "/tutorial Pedir sitio web de *Tutoriales* de ALSW\n";
  Mensaje += "/noticias Pedir sitio web de *Noticias* de ALSW\n";
  Mensaje += "/discord Pedir Comunidad de *Discord* de ALSW\n"
  Mensaje += "/codigo Pedir codigo del proyecto\n";
  Mensaje += "/web Pedir pagina Web del proyectyo\n";
  Mensaje += "/video Pedir video del proyecto\n";
  Mensaje += "/error Pedir sitio web para reportar errores\n"
  Mensaje += "/ayuda  Para pedir ayuda de los comandos\n";

  bot.sendMessage(ID, Mensaje, {
    parse_mode: "Markdown"
  });
}


function MensajeDepuracion() {
  var Mensaje = "Se Cambio estado ";
  bot.sendMessage(ID, Mensaje, {
    parse_mode: "Markdown"
  });
}

MiParse.setEncoding('utf8');

MiParse.on('data', function(data) {
  var Mensaje = data.split('/n');
  console.log(Mensaje);
});
