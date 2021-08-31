const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");
const {
  ObtenerDataVideo,
  BuscarVideoRecursivamente,
  ReiniciarFolder,
} = require("./funciones");

function ObtenerURLYoutube(url) {
  //No entiendo pero funciona
  let Pagina;
  try {
    Pagina = fs.readFileSync(`./_${url}.md`, "UTF8");
  } catch (err) {
    try {
      Pagina = fs.readFileSync(`./_${url}/index.md`, "UTF8");
    } catch (e) {
      return url;
    }
  }

  const Contenido = yaml.loadFront(Pagina);
  if (Contenido.video_id) {
    return `https://youtu.be/${Contenido.video_id}`;
  } else if (Contenido.playlist_id) {
    return `https://www.youtube.com/playlist?list=${Contenido.playlist_id}`;
  }
}

function ImprimirData(Titulo, CantidadLink, CantidadTotal) {
  Porcentaje = parseFloat((100 * CantidadLink) / CantidadTotal).toFixed(2);
  console.log(`${Titulo}: ${CantidadLink} ${Porcentaje}%`);
}

function AgregarSeoMostar(descripcion, Cantidad, Actualizar) {
  let Lineas = descripcion.split(/\n/);
  let LongitudLinea = 90;
  if (descripcion.length <= LongitudLinea * 2 && Lineas.length <= 2) {
    descripcion += `👇 👇 👇\n`;
    if (Actualizar) Cantidad.SeoMostarActivo++;
    Cantidad.SeoMostar++;
  } else if (Lineas[0].length <= LongitudLinea * 2) {
    let D = Lineas[0];
    D += `\n👇 👇 👇`;
    for (var i = 1; i < Lineas.length; i++) {
      D += `\n` + Lineas[i];
    }
    descripcion = D;
    if (Actualizar) Cantidad.SeoMostarActivo++;
    Cantidad.SeoMostar++;
  }
  return descripcion;
}

async function CrearDescripciones(videos) {
  let CantidadVideos = videos.length;
  let ActivadoAdsGlobal = false;
  let Cantidad = new Object();
  Cantidad.Colaboradores = 0;
  Cantidad.SeoMostar = 0;
  Cantidad.SeoMostarActivo = 0;
  Cantidad.Links = 0;
  Cantidad.Codigo = 0;
  Cantidad.Indice = 0;
  Cantidad.Piezas = 0;
  Cantidad.Costun = 0;
  Cantidad.Ads = 0;
  Cantidad.Video = 0;
  Cantidad.NuevoSistema = 0;

  await ReiniciarFolder("./descripciones");
  await ReiniciarFolder("./actualizado");

  for (let i = 0; i < videos.length; i++) {
    const data = videos[i].data;
    const pageURL = videos[i].pageURL;
    const playlist = videos[i].playlist;

    let descripcion = "";

    // Descripcion
    let content = data.__content.trim();
    descripcion += `${content}\n`;

    descripcion = AgregarSeoMostar(descripcion, Cantidad, data.actualizado);

    const AdsGlobal = path.join(__dirname, "ads.txt");
    try {
      if (fs.existsSync(AdsGlobal)) {
        ActivadoAdsGlobal = true;
        let ADS = fs.readFileSync(AdsGlobal);
        descripcion += `\n${ADS}`;
      }
    } catch (err) {
      console.error(err);
    }

    // ADS
    if (data.ads) {
      CantidadAds++;
      for (let i = 0; i < data.ads.length; ++i) {
        descripcion += `\n${data.ads[i].title} ${data.ads[i].url}\n`;
      }
    }

    // TODO: Mejor Algorititmo
    // Siquiente Video / Playlist
    let SiquienteVideo;
    if (i !== videos.length - 1) {
      if (
        pageURL.substring(0, pageURL.lastIndexOf("/")) ===
        videos[i + 1].pageURL.substring(
          0,
          videos[i + 1].pageURL.lastIndexOf("/")
        )
      ) {
        SiquienteVideo = videos[i + 1].data.video_id;
      } else {
        SiquienteVideo = false;
      }
    } else {
      SiquienteVideo = false;
    }

    if (playlist || SiquienteVideo) {
      descripcion += `\n`;
      if (SiquienteVideo) {
        descripcion += `🎥 Siguiente video: https://youtu.be/${SiquienteVideo}\n`;
      }
      if (playlist) {
        let NombrePlaylist = videos[i].playlistName;
        descripcion += `🎥 Playlist(${NombrePlaylist}): https://www.youtube.com/playlist?list=${playlist}\n`;
      }
    }

    // Videos
    if (data.videos) {
      Cantidad.Video++;
      descripcion += "\nVideo mencionados:\n";
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

    // Codigo
    if (data.repository || data.web_editor) {
      Cantidad.Codigo++;
      descripcion += `\n💻 Codigo: https://nocheprogramacion.com/${pageURL}.html\n`;
    } else {
      descripcion += `\n🖥 Articulo: https://nocheprogramacion.com/${pageURL}.html\n`;
    }

    // Links
    if (data.links) {
      Cantidad.Links++;
      descripcion += "\nLink referencie:\n";
      for (let i = 0; i < data.links.length; ++i) {
        const url = data.links[i].url;
        if (/https?:\/\/.*/.test(url)) {
          descripcion += `🔗 ${data.links[i].title}: ${url}\n`;
        } else {
          descripcion += `🔗 ${data.links[i].title}: https://nocheprogramacion.com/${url}\n`;
        }
      }
    }

    // Link de piesas
    if (data.piezas) {
      Cantidad.Piezas++;
      descripcion += "\nComponentes electronicos mencionado video:\n";
      for (let i = 0; i < data.piezas.length; ++i) {
        const url = data.piezas[i].url;
        if (url) {
          if (/https?:\/\/.*/.test(url)) {
            descripcion += `🤖 ${data.piezas[i].title}: ${url}\n`;
          } else {
            descripcion += `🤖 ${data.piezas[i].title}: https://nocheprogramacion.com${url}\n`;
          }
        } else {
          descripcion += `🤖 ${data.piezas[i].title}\n`;
        }
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
      descripcion += "\n🕓 Indice:\n";
      for (let i = 0; i < data.topics.length; ++i) {
        descripcion += `${data.topics[i].time} ${data.topics[i].title}\n`;
      }
    }

    // Agradecer a colaboradores
    if (data.colaboradores) {
      Cantidad.Colaboradores++;
      descripcion += "\nVideo gracias a los Colaboradore:\n";
      for (let i = 0; i < data.colaboradores.length; ++i) {
        descripcion += `🧙🏼‍♂️${data.colaboradores[i].title} - ${data.colaboradores[i].colaborador}\n`;
      }
    }

    // TODO: Crear nuevo grupo de Telegram y Whatsapp ?

    // Links Generales
    descripcion += `
👏🏽 Subscribe: https://www.youtube.com/alswnet?sub_confirmation=1
💖 Membreria: https://www.youtube.com/alswnet/join
🚂 Sitio Web: http://nocheprogramacion.com
💬 Discord: https://nocheprogramacion.com/discord
👾 Comparte tu creación! https://nocheprogramacion.com/tucodigo
🚩 Sugerir Temas: https://github.com/alswnet/NocheProgramacion/issues/new
💡 GitHub: https://github.com/alswnet
☕ Donar un café: https://www.buymeacoffee.com/alswnet
💖 Apoyo: https://nocheprogramacion.com/apoyo
💰 Donación: https://nocheprogramacion.com/donar
🌎 Noticias: https://programacion.news
🐦 Twitter: https://twitter.com/alswnet
📸 Instagram: https://www.instagram.com/alswnet
👍 Facebook: https://www.facebook.com/alswnet
👥 Grupo Facebook: https://www.facebook.com/groups/chepecarlosclub
🔭 Telegram: https://t.me/alswnet
🕹 Canal VideoJuegos: https://www.youtube.com/channel/UC-QPTA-oIQf59SVA8ckpMXA?sub_confirmation=1
🎈 Twitch: https://www.twitch.tv/alswnet`;

    // if (data.tags) {
    //   descripcion += `\n\n#ALSW`;
    //   for (let i = 0; i < data.tags.length; ++i) {
    //     descripcion += ` #` + data.tags[i];
    //   }
    //   // descripcion += `\n`;
    // }

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
      fs.writeFileSync(`actualizado/${data.video_id}.txt`, descripcion);
    }

    let tipo = videos[i].pageURL.split("/")[0];
    NombreArchivo = `${tipo}_${NombreArchivo}`;

    fs.writeFileSync(`descripciones/${NombreArchivo}.txt`, descripcion);
    fs.writeFileSync(`descripciones/Zen_${data.video_id}.txt`, descripcion);
  }
  console.log(`Cantidad total videos: ${CantidadVideos}`);
  ImprimirData("Colaboradores", Cantidad.Colaboradores, CantidadVideos);
  ImprimirData("Links", Cantidad.Links, CantidadVideos);
  ImprimirData("Indices", Cantidad.Indice, CantidadVideos);
  ImprimirData("Piezas", Cantidad.Piezas, CantidadVideos);
  ImprimirData("Extras", Cantidad.Costun, CantidadVideos);
  ImprimirData("Videos", Cantidad.Video, CantidadVideos);
  ImprimirData("Codigo", Cantidad.Codigo, CantidadVideos);
  ImprimirData("Ads", Cantidad.Ads, CantidadVideos);
  ImprimirData("SeoMostar", Cantidad.SeoMostar, CantidadVideos);
  ImprimirData("SeoMostar Activos", Cantidad.SeoMostarActivo, CantidadVideos);
  ImprimirData("Nuevo Sistema", Cantidad.NuevoSistema, CantidadVideos);
  console.log(`Ads Global: ${ActivadoAdsGlobal}`);
}

(() => {
  console.log(
    "💫 Generador de descripcion de NocheProgramacion para Youtube 💫"
  );
  CrearDescripciones(ObtenerDataVideo());
})();
