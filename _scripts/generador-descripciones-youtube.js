/*
Generador de Descripción para video de YouTube 
Para sistema de NocheProgramacion
*/

const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");
const {
  ObtenerDataVideo,
  BuscarVideoRecursivamente,
  ReiniciarFolder,
  ObtenerURLYoutube,
} = require("./funciones");

function ImprimirData(Titulo, CantidadLink, CantidadTotal) {
  Porcentaje = parseFloat((100 * CantidadLink) / CantidadTotal).toFixed(2);
  console.log(`${Titulo}: ${CantidadLink} ${Porcentaje}%`);
}

function AgregarSeoMostar(descripcion, Cantidad, Actualizar, Publicidad) {
  let Lineas = descripcion.split(/\n/);
  let LongitudLinea = 90;

  if (descripcion.length <= LongitudLinea) {
    descripcion += `\n`;
  }

  if (descripcion.length <= LongitudLinea * 2 && Lineas.length <= 2) {
    // descripcion = AgregarADS(descripcion, Publicidad);
    descripcion += `${Publicidad}`;
    descripcion += `👇 👇 HAZ CLICK 👇 👇\n`;
    if (Actualizar) Cantidad.SeoMostarActivo++;
    Cantidad.SeoMostar++;
  } else if (Lineas[0].length <= LongitudLinea * 2) {
    let D = Lineas[0];
    descripcion += `${Publicidad}`;
    // descripcion = AgregarADS(descripcion, Publicidad);
    D += `\n👇 👇 HAZ CLICK 👇 👇`;
    for (var i = 1; i < Lineas.length; i++) {
      D += `\n` + Lineas[i];
    }
    descripcion = D;
    if (Actualizar) Cantidad.SeoMostarActivo++;
    Cantidad.SeoMostar++;
  }
  return descripcion;
}

function LinkAmazon(codigo, producto) {
  let texto = "";
  for (let i = 0; i < codigo["amazon"].length; i++) {
    for (var key in producto) {
      if (codigo["amazon"][i]["pais"].toLowerCase() == key.toLowerCase()) {
        if ("string" == typeof producto[key]) {
          texto += `    Amazon-${key.toUpperCase()}: ${
            codigo["amazon"][i]["url"]
          }/dp/${producto[key]}/ref=nosim?tag=${
            codigo["amazon"][i]["codigo"]
          }\n`;
        } else {
          texto += `    Amazon-${key.toUpperCase()}:\n`;
          for (let z = 0; z < producto[key].length; z++) {
            texto += `      ${codigo["amazon"][i]["url"]}/dp/${producto[key][z]}/ref=nosim?tag=${codigo["amazon"][i]["codigo"]}\n`;
          }
        }
      }
    }
  }
  return texto;
}

async function CrearDescripciones(videos) {
  let CantidadVideos = videos.length;
  let ActivadoAdsGlobal = false;
  let Cantidad = new Object();
  Cantidad.Colaboradores = 0;
  Cantidad.SeoMostar = 0;
  Cantidad.SeoMostarActivo = 0;
  Cantidad.Miembros = 0;
  Cantidad.ParaMiembros = 0;
  Cantidad.Links = 0;
  Cantidad.Codigo = 0;
  Cantidad.Indice = 0;
  Cantidad.Piezas = 0;
  Cantidad.Remake = 0;
  Cantidad.Costun = 0;
  Cantidad.Ads = 0;
  Cantidad.Video = 0;
  Cantidad.playlist = 0;
  Cantidad.log = 0;
  Cantidad.NuevoSistema = 0;

  await ReiniciarFolder("./descripciones");
  await ReiniciarFolder("./actualizado");

  const ArchivoAds = path.join(__dirname, "ads.txt");
  let AdsGlobal = "";
  try {
    if (fs.existsSync(ArchivoAds)) {
      ActivadoAdsGlobal = true;
      data = await fs.readFileSync(ArchivoAds);
      AdsGlobal = data.toString();
      console.log(`Ads Global: '${AdsGlobal}'`);
    }
  } catch (err) {
    console.error(err);
  }

  const ArchivoRedes = path.join(__dirname, "redes.txt");
  let RedesGlobal = "";
  try {
    if (fs.existsSync(ArchivoRedes)) {
      data = await fs.readFileSync(ArchivoRedes);
      RedesGlobal = data.toString();
      console.log("Link y Redes: True");
    }
  } catch (err) {
    console.error(err);
  }

  let AmazonNoEncontrado = 0;
  const ArchivoAmazon = path.join(__dirname, "amazon-code.md");
  let AmazonEncontrado = 0;
  let CodigoAmazon = "";
  try {
    if (fs.existsSync(ArchivoAmazon)) {
      const contenido = fs.readFileSync(ArchivoAmazon, "UTF8");
      CodigoAmazon = yaml.loadFront(contenido);
      data.toString();
      console.log(`Codigo afilacion Amazon:`);
      for (let i = 0; i < CodigoAmazon["amazon"].length; i++) {
        console.log(
          "\t" +
            CodigoAmazon["amazon"][i]["pais"] +
            " - " +
            CodigoAmazon["amazon"][i]["codigo"]
        );
      }
    }
  } catch (err) {
    console.error(err);
  }

  const ArchivoProductos = path.join(__dirname, "producto.md");
  let ProductoAmazon;
  try {
    const contenido = fs.readFileSync(ArchivoProductos, "UTF8");
    ProductoAmazon = yaml.loadFront(contenido);
  } catch (err) {
    console.error(err);
  }

  for (let i = 0; i < videos.length; i++) {
    const data = videos[i].data;
    const pageURL = videos[i].pageURL;
    const playlist = videos[i].playlist;

    let descripcion = "";

    if (!data.actualizado) {
      continue;
    }

    if (data.para_miembros) {
      Cantidad.ParaMiembros++;
      descripcion += `🦾 Avances Exclusivo para Miembros del Canal ChepeCarlos 🦾

👉 Quieres verlo, únete aquí: https://www.youtube.com/alswnet/join 👈

Este Video sera publico y accesible por toda la comunidad en el futuro.

🔭 Mira todos los video disponible para Miembros en: https://nocheprogramacion.com/miembros`;
    } else {
      // Descripción
      let content = data.__content.trim();
      descripcion += `${content}\n`;

      descripcion = AgregarSeoMostar(
        descripcion,
        Cantidad,
        data.actualizado,
        AdsGlobal
      );

      // ADS
      if (data.ads) {
        Cantidad.Ads++;
        for (let i = 0; i < data.ads.length; ++i) {
          descripcion += `\n${data.ads[i].title} ${data.ads[i].url}\n`;
        }
      }

      // Remake
      if (data.remake) {
        Cantidad.Remake++;
        url = ObtenerURLYoutube(data.remake);
        descripcion =
          `Existe una versión NUEVA 👀 o actualización de este video: ${url}\n` +
          descripcion;
      }

      // Correcciones
      if(data.log){
        Cantidad.log++;
        descripcion += `\n⚠️ Correcciones ⚠️:\n`;
        for (let i = 0; i < data.log.length; ++i) {
          const mejora = data.log[i].title;
          console.log(mejora);
          descripcion += ` ✦ ${mejora} \n`;
        }
      }

      // TODO: Mejor Algoritmo
      // Siguiente Video / Playlist
      let siguienteVideo;
      let NombreSiguienteVideo;
      if (i !== videos.length - 1) {
        if (
          pageURL.substring(0, pageURL.lastIndexOf("/")) ===
          videos[i + 1].pageURL.substring(
            0,
            videos[i + 1].pageURL.lastIndexOf("/")
          )
        ) {
          siguienteVideo = videos[i + 1].data.video_id;
          NombreSiguienteVideo = videos[i + 1].data.title;
        } else {
          siguienteVideo = false;
        }
      } else {
        siguienteVideo = false;
      }

      let anteriorVideo;
      let tituloAnteriorVideo;
      if (i !== 0) {
        if (
          pageURL.substring(0, pageURL.lastIndexOf("/")) ===
          videos[i - 1].pageURL.substring(
            0,
            videos[i - 1].pageURL.lastIndexOf("/")
          )
        ) {
          anteriorVideo = videos[i - 1].data.video_id;
          tituloAnteriorVideo = videos[i - 1].data.title;
        } else {
          previousID = false;
        }
      } else {
        previousID = false;
      }

      if (playlist || siguienteVideo || anteriorVideo) {
        Cantidad.playlist++;
        descripcion += "\n";

        // Anterior video
        if (anteriorVideo && playlist) {
          descripcion += `👈 Anterior Video "${tituloAnteriorVideo}": https://youtu.be/${anteriorVideo}?list=${playlist}\n`;
        } else if (anteriorVideo) {
          descripcion += `👈 Anterior Video "${tituloAnteriorVideo}": https://youtu.be/${anteriorVideo}\n`;
        }

        // Siguiente video
        if (siguienteVideo && playlist) {
          descripcion += `👉 Siguiente Video "${NombreSiguienteVideo}" : https://youtu.be/${siguienteVideo}?list=${playlist}\n`;
        } else if (siguienteVideo) {
          descripcion += `👉 Siguiente Video "${NombreSiguienteVideo}" : https://youtu.be/${siguienteVideo}\n`;
        }

        // Serie
        if (playlist) {
          let NombrePlaylist = videos[i].playlistName;
          descripcion += `🎥 Playlist(${NombrePlaylist}): https://www.youtube.com/playlist?list=${playlist}\n`;
        }
      }

      // Videos
      if (data.videos) {
        Cantidad.Video++;
        descripcion += "\nVideos mencionados:\n";
        for (let i = 0; i < data.videos.length; ++i) {
          if (data.videos[i].video_id) {
            descripcion += `🎞 ${data.videos[i].title}: https://youtu.be/${data.videos[i].video_id}\n`;
          } else if (data.videos[i].url) {
            let url = data.videos[i].url;
            if (/https?:\/\/.*/.test(url)) {
              descripcion += `🎞 ${data.videos[i].title}: ${url}\n`;
            } else {
              url = ObtenerURLYoutube(data.videos[i].url);
              descripcion += `🎞 ${data.videos[i].title}: ${url}\n`;
            }
          }
        }
      }

      // Código
      if (data.repository || data.web_editor) {
        Cantidad.Codigo++;
        descripcion += `\n💻 Código: https://nocheprogramacion.com/${pageURL}.html\n`;
      } else {
        descripcion += `\n🖥 Articulo: https://nocheprogramacion.com/${pageURL}.html\n`;
      }

      // Links
      if (data.links) {
        Cantidad.Links++;
        descripcion += "\nLink referencia:\n";
        for (let i = 0; i < data.links.length; ++i) {
          const url = data.links[i].url;
          if (/https?:\/\/.*/.test(url)) {
            descripcion += `🔗 ${data.links[i].title}: ${url}\n`;
          } else {
            descripcion += `🔗 ${data.links[i].title}: https://nocheprogramacion.com/${url}\n`;
          }
        }
      }

      // Link de piezas y amazon
      if (data.piezas) {
        Cantidad.Piezas++;
        let SiAmazon = false;
        descripcion += "\nComponentes electrónicos:\n";
        for (let i = 0; i < data.piezas.length; i++) {
          const url = data.piezas[i].url;
          if (url) {
            if (/https?:\/\/.*/.test(url)) {
              descripcion += `  🤖 ${data.piezas[i].title}: ${url}\n`;
            } else {
              descripcion += `  🤖 ${data.piezas[i].title}: https://nocheprogramacion.com${url}\n`;
            }
          } else {
            descripcion += `  🤖 ${data.piezas[i].title}\n`;
          }

          let EncontradoAmazon = false;
          for (let j = 0; j < ProductoAmazon["productos"].length; j++) {
            if (data.piezas[i].title) {
              if (
                ProductoAmazon["productos"][j]["name"].toLowerCase() ==
                data.piezas[i].title.toLowerCase()
              ) {
                EncontradoAmazon = true;
                SiAmazon = true;
                descripcion += LinkAmazon(
                  CodigoAmazon,
                  ProductoAmazon["productos"][j]
                );
              }
            }
          }

          if (!EncontradoAmazon) {
            if (data.piezas[i].title === null) {
              console.log("error");
              // console.log(videos[i].pageURL);
              console.log(pageURL);
            }
            AmazonNoEncontrado++;
            console.log(
              "\x1b[33m%s\x1b[0m",
              `No encontrado ${AmazonNoEncontrado} - ${data.piezas[i].title} - ${data.video_id} - ${data.title}`
            );
          } else {
            AmazonEncontrado++;
          }
        }
        if (SiAmazon) {
          descripcion += `Link de Afilaron de amazon, ganamos una comisión si los usas\n`;
        }
      }

      // Partes Extras
      if (data.custom_sections) {
        Cantidad.Costun++;
        descripcion += `\nLink Extras:\n`;
        for (let i = 0; i < data.custom_sections.length; ++i) {
          if (data.custom_sections[i].title) {
            descripcion += `✪ ${data.custom_sections[i].title}:\n`;
            for (let j = 0; j < data.custom_sections[i].items.length; ++j) {
              const url = data.custom_sections[i].items[j].url;
              const title = data.custom_sections[i].items[j].title;
              descripcion += `  `;
              if (/https?:\/\/.*/.test(url)) {
                descripcion += `➤ ${title}: ${url}\n`;
              } else {
                descripcion += `➤ ${title}: https://nocheprogramacion.com${url}\n`;
              }
            }
          }
        }
      }

      // Indice del video
      if (data.topics) {
        Cantidad.Indice++;
        descripcion += "\n🕓 Índice:\n";
        for (let i = 0; i < data.topics.length; ++i) {
          descripcion += `${data.topics[i].time} ${data.topics[i].title}\n`;
        }
      }

      // Links Generales
      descripcion += `\n${RedesGlobal}`;

      // Agradecer a colaboradores
      if (data.actualizado) {
        if (data.colaboradores) {
          Cantidad.Colaboradores++;
          descripcion += "\nCreado con los Aliados:\n";
          for (let i = 0; i < data.colaboradores.length; ++i) {
            descripcion += `  🧙🏼‍♂️ ${data.colaboradores[i].title} - ${data.colaboradores[i].colaborador}\n`;
          }
        }
      }

      descripcion += `\n#ChepeCarlos`;
      if (data.tags) {
        for (let i = 0; i < data.tags.length; ++i) {
          if (data.tags[i] == "shorts") {
            descripcion += ` #` + data.tags[i];
          }
        }
      }
      descripcion += `\n`;

      // Miembros
      if (data.miembros) {
        Cantidad.Miembros++;
        descripcion +=
          "\n🦾 Creado gracias al Apoyo de Miembros(Patrocinadores):\n";
        for (let i = 0; i < data.miembros.length; ++i) {
          let nivelActual = data.miembros[i];
          descripcion += `${nivelActual.title}: `;
          let ListaMiembros = nivelActual.items;
          for (let i = 0; i < ListaMiembros.length; i++) {
            descripcion += `${ListaMiembros[i].title}`;
            if (i < ListaMiembros.length - 1) {
              descripcion += `, `;
            } else {
              descripcion += `.`;
            }
          }
          descripcion += `\n`;
        }

        descripcion += `\n🔭 Agrega tu nombre, Únete tú también https://www.youtube.com/@chepecarlo/join 🔭`;
        descripcion += `\n👊 Avances Exclusivo para Miembros: https://nocheprogramacion.com/miembros 👊`;
      } else {
        descripcion += `\n👊 Avances Exclusivo para Miembros: https://nocheprogramacion.com/miembros 👊`;
        descripcion += `\n🔭 Quieres apoyar, conviértete en Miembro: https://www.youtube.com/@chepecarlo/join 🔭`;
      }
    }

    // descripcion += `\nEsta descripción fue auto-generada. Si ves algún problema, por favor reportarlo en https://github.com/alswnet/NocheProgramacion/issues/new`;

    let NombreArchivo = `${data.video_id}`;
    if (data.video_number) {
      NombreArchivo = `${data.video_number}_${NombreArchivo}`;
    }
    if (data.course_number) {
      NombreArchivo = `${data.course_number}.${NombreArchivo}`;
    }

    if (data.actualizado) {
      Cantidad.NuevoSistema++;
      // TODO: Quitar cuando generador use meses y años
      let FechaArticulo = new Date(data.date);
      let mes = FechaArticulo.getMonth() + 1;
      let anno = FechaArticulo.getFullYear();
      let Folder = `actualizado/${anno}`;

      // console.log(`fecha ${anno}/${mes} ${FechaArticulo.getMonth()} --${data.date}- ${data.title}`)

      if (!fs.existsSync(Folder)) {
        await fs.mkdirSync(Folder);
      }
      if (mes < 10) {
        Folder += `/0${mes}`;
      } else {
        Folder += `/${mes}`;
      }
      if (!fs.existsSync(Folder)) {
        // console.log(Folder);
        await fs.mkdirSync(Folder);
      }
      fs.writeFileSync(`${Folder}/${data.video_id}.txt`, descripcion);
    }

    // let tipo = videos[i].pageURL.split("/")[0];
    // NombreArchivo = `${tipo}_${NombreArchivo}`;

    // fs.writeFileSync(`descripciones/${NombreArchivo}.txt`, descripcion);
    // fs.writeFileSync(`descripciones/Zen_${data.video_id}.txt`, descripcion);
  }

  console.log(`Cantidad total videos: ${CantidadVideos}`);
  ImprimirData("Miembros", Cantidad.Miembros, CantidadVideos);
  ImprimirData("Para Miembros", Cantidad.ParaMiembros, CantidadVideos);
  ImprimirData("Playlist", Cantidad.playlist, CantidadVideos);
  ImprimirData("Colaboradores", Cantidad.Colaboradores, CantidadVideos);
  ImprimirData("Links", Cantidad.Links, CantidadVideos);
  ImprimirData("Indices", Cantidad.Indice, CantidadVideos);
  ImprimirData("Piezas", Cantidad.Piezas, CantidadVideos);
  ImprimirData("Extras", Cantidad.Costun, CantidadVideos);
  ImprimirData("Videos", Cantidad.Video, CantidadVideos);
  ImprimirData("Código", Cantidad.Codigo, CantidadVideos);
  ImprimirData("Remake", Cantidad.Remake, CantidadVideos);
  ImprimirData("Log", Cantidad.log, CantidadVideos);
  ImprimirData("Ads", Cantidad.Ads, CantidadVideos);
  ImprimirData("SeoMostar", Cantidad.SeoMostar, CantidadVideos);
  ImprimirData("SeoMostar Activos", Cantidad.SeoMostarActivo, CantidadVideos);
  ImprimirData("Nuevo Sistema", Cantidad.NuevoSistema, CantidadVideos);
  console.log(
    "\x1b[33m%s\x1b[0m",
    `Amazon No encontrado: ${AmazonNoEncontrado}`
  );
  console.log(`Amazon encontrado: ${AmazonEncontrado}`);

  console.log(`Ads Global: ${ActivadoAdsGlobal}`);
}

(() => {
  console.log(
    "💫 Generador de descripcion de NocheProgramación para YouTube 💫"
  );
  CrearDescripciones(ObtenerDataVideo());
})();
