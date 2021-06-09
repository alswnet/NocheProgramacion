const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");

function findVideoFilesRecursive(dir, arrayOfFiles) {
  const files = fs.readdirSync(dir);

  arrayOfFiles = arrayOfFiles || [];

  for (const file of files) {
    if (fs.statSync(`${dir}/${file}`).isDirectory()) {
      arrayOfFiles = findVideoFilesRecursive(`${dir}/${file}`, arrayOfFiles);
    } else {
      if (
        file !== "index.md" &&
        file.substring(file.length - 3, file.length) === ".md"
      ) {
        arrayOfFiles.push(path.join(dir, "/", file));
      }
    }
  }

  return arrayOfFiles;
}

function getPlaylist(file) {
  const series = file.substring(0, file.lastIndexOf("/")) + "/index.md";
  const content = fs.readFileSync(series);
  const parsed = yaml.loadFront(content);
  if (parsed.playlist_id) {
    return parsed.playlist_id;
  }
  return false;
}

function getVideoData() {
  const directories = [
    "_Tutoriales",
    "_Cursos",
    "_shorts",
    "_series",
    "_RetoProgramacion",
    "_Grabaciones",
    "_invitados",
    "_mas/bodega"
  ];

  let files = [];
  for (const dir of directories) {
    findVideoFilesRecursive(dir, files);
  }

  const videos = [];

  for (const file of files) {
    const content = fs.readFileSync(`./${file}`, "UTF8");
    const parsed = yaml.loadFront(content);
    let url = file.substring(1);
    url = url.substring(0, url.length - 3);
    videos.push({
      pageURL: url,
      data: parsed,
      playlist: getPlaylist(file)
    });
  }

  return videos;
}

function primeDirectory(dir) {
  fs.rmdirSync(
    dir,
    {
      recursive: true
    },
    err => {
      if (err) {
        throw err;
      }
    }
  );

  fs.mkdirSync(dir, err => {
    if (err) {
      throw err;
    }
  });
}

function getVideoID(url) {
  const location = url.substring(1, url.length);
  let page;
  try {
    page = fs.readFileSync(`./_${location}.md`, "UTF8");
  } catch (err) {
    try {
      const files = fs.readdirSync(`./_${location}`);
      page = fs.readFileSync(`./_${location}/${files[0]}.md`, "UTF8");
    } catch (e) {
      return url;
    }
  }
  const parsed_content = yaml.loadFront(page);
  return `https://youtu.be/${parsed_content.video_id}`;
}

function DosDecimales(Numero, Cantidad) {
  return Numero + " " + parseFloat((100 * Numero) / Cantidad).toFixed(2) + "%";
}

function AgregarSeoMostar(data, descripcion) {
  // TODO: no Activar si hay ads
  let Saltos = descripcion.split(/\n/);
  let CantidadSaltos = Saltos.length;
  let LongitudTotal = descripcion.length;

  if (CantidadSaltos <= 2 && LongitudTotal <= 90) {
    return true;
  }
  return false;
}

function writeDescriptions(videos) {
  let CantidadLinks = 0;
  let CantidadIndice = 0;
  let CantidadPiesas = 0;
  let CantidadCostun = 0;
  let CantidadAds = 0;
  let CantidadVideo = 0;
  let CantidadSeoMostar = 0;
  let NuevoSistema = 0;

  primeDirectory("./descripciones");
  primeDirectory("./actualizado");

  for (let i = 0; i < videos.length; i++) {
    const data = videos[i].data;
    const pageURL = videos[i].pageURL;
    const playlist = videos[i].playlist;

    let description = "";

    // Descripcion
    let content = data.__content.trim();
    description += `${content}\n`;

    // SeoMostar
    if (AgregarSeoMostar(data, description)) {
      CantidadSeoMostar++;
      description += `\n👇 👇 👇\n`;
    }

    // ADS
    if (data.ads) {
      CantidadAds++;
      for (let i = 0; i < data.ads.length; ++i) {
        description += `\n${data.ads[i].title} ${data.ads[i].url}\n`;
      }
    }

    // Codigo
    if (data.repository || data.web_editor) {
      description += `\n💻 Codigo: https://nocheprogramacion.com/${pageURL}.html\n`;
    } else {
      description += `\n🖥 Articulo: https://nocheprogramacion.com/${pageURL}.html\n`;
    }

    // Next Video / Playlist
    let nextID;
    if (i !== videos.length - 1) {
      if (
        pageURL.substring(0, pageURL.lastIndexOf("/")) ===
        videos[i + 1].pageURL.substring(
          0,
          videos[i + 1].pageURL.lastIndexOf("/")
        )
      ) {
        nextID = videos[i + 1].data.video_id;
      } else {
        nextID = false;
      }
    } else {
      nextID = false;
    }

    if (playlist || nextID) {
      description += `\n`;
      if (nextID) {
        description += `🎥 Siquiente video: https://youtu.be/${nextID}\n`;
      }
      if (playlist) {
        description += `🎥 Playlist: https://www.youtube.com/playlist?list=${playlist}\n`;
      }
    }

    // Links
    if (data.links) {
      CantidadLinks++;
      description += "\nLink referencie:\n";
      for (let i = 0; i < data.links.length; ++i) {
        const url = data.links[i].url;
        if (/https?:\/\/.*/.test(url)) {
          description += `🔗 ${data.links[i].title}: ${url}\n`;
        } else {
          description += `🔗 ${data.links[i].title}: https://nocheprogramacion.com/${url}\n`;
        }
      }
    }

    // Link de piesas
    if (data.piezas) {
      CantidadPiesas++;
      description += "\nComponentes electronicos mencionado video:\n";
      for (let i = 0; i < data.piezas.length; ++i) {
        const url = data.piezas[i].url;
        if (url) {
          if (/https?:\/\/.*/.test(url)) {
            description += `🤖 ${data.piezas[i].title}: ${url}\n`;
          } else {
            description += `🤖 ${data.piezas[i].title}: https://nocheprogramacion.com${url}\n`;
          }
        } else {
          description += `🤖 ${data.piezas[i].title}\n`;
        }
      }
    }

    // Videos
    if (data.videos) {
      CantidadVideo++;
      description += "\nOtros video mencionados en video:\n";
      for (let i = 0; i < data.videos.length; ++i) {
        if (data.videos[i].video_id) {
          description += `🎥 ${data.videos[i].title}: https://youtu.be/${data.videos[i].video_id}\n`;
        } else if (data.videos[i].url) {
          const url = data.videos[i].url;
          if (/https?:\/\/.*/.test(url)) {
            description += `🎥 ${data.videos[i].title}: ${url}\n`;
          } else {
            description += `🎥 ${data.videos[i].title}: https://nocheprogramacion.com${url}\n`;
          }
        }
      }
    }

    // Partes Extras
    if (data.custom_sections) {
      CantidadCostun++;
      description += `\nLink:\n`;
      for (let i = 0; i < data.custom_sections.length; ++i) {
        if (data.custom_sections[i].title) {
          description += `✪ ${data.custom_sections[i].title}:\n`;
          for (let j = 0; j < data.custom_sections[i].items.length; ++j) {
            const url = data.custom_sections[i].items[j].url;
            const title = data.custom_sections[i].items[j].title;
            if (/https?:\/\/.*/.test(url)) {
              description += `➤ ${title}: ${url}\n`;
            } else {
              description += `➤ ${title}: https://nocheprogramacion.com${url}\n`;
            }
          }
        }
      }
    }

    // Indice del video
    if (data.topics) {
      CantidadIndice++;
      description += "\n🕓 Indice:\n";
      for (let i = 0; i < data.topics.length; ++i) {
        description += `${data.topics[i].time} ${data.topics[i].title}\n`;
      }
    }
    // Links Generales
    description += `
👏🏽 Subscribe: https://www.youtube.com/alswnet?sub_confirmation=1
🚂 Sitio Web: http://nocheprogramacion.com
👾 Comparte tu creación! https://nocheprogramacion.com/tucodigo
🚩 Sugerir Temas: https://github.com/alswnet/NocheProgramacion/issues/new
💡 GitHub: https://github.com/alswnet
💬 Discord: https://nocheprogramacion.com/discord
☕ Compranos un cafe: https://www.buymeacoffee.com/alswnet
💖 Apoyo: https://nocheprogramacion.com/apoyo
💰 Donacion: https://nocheprogramacion.com/donar
🌎 Noticias: https://programacion.news
🖋️ Twitter: https://twitter.com/alswnet
📸 Instagram: https://www.instagram.com/alswnet
🔭 Telegram: https://t.me/alswnet
🕹 Canal VideoJuegos: https://www.youtube.com/channel/UC-QPTA-oIQf59SVA8ckpMXA?sub_confirmation=1`;

    // if (data.tags) {
    //   description += `\n\n#ALSW`;
    //   for (let i = 0; i < data.tags.length; ++i) {
    //     description += ` #` + data.tags[i];
    //   }
    //   // description += `\n`;
    // }

    // description += `\nEsta descripción fue auto-generada. Si ves algún problema, por favor reportarlo en https://github.com/alswnet/NocheProgramacion/issues/new`;

    let NombreArchivo = `${data.video_id}`;
    if (data.video_number) {
      NombreArchivo = `${data.video_number}_${NombreArchivo}`;
    }
    if (data.course_number) {
      NombreArchivo = `${data.course_number}.${NombreArchivo}`;
    }

    if (data.actualizado) {
      NuevoSistema++;
      fs.writeFileSync(`actualizado/${data.video_id}.txt`, description);
    }

    let tipo = videos[i].pageURL.split("/")[0];
    NombreArchivo = `${tipo}_${NombreArchivo}`;

    fs.writeFileSync(`descripciones/${NombreArchivo}.txt`, description);
    fs.writeFileSync(`descripciones/Zen_${data.video_id}.txt`, description);
  }
  console.log("Cantidad total: " + videos.length);
  console.log(`Links: ${DosDecimales(CantidadLinks, videos.length)}`);
  console.log(`Indices: ${DosDecimales(CantidadIndice, videos.length)}`);
  console.log(`Piezas: ${DosDecimales(CantidadPiesas, videos.length)}`);
  console.log(`Extras: ${DosDecimales(CantidadCostun, videos.length)}`);
  console.log(`Videos: ${DosDecimales(CantidadVideo, videos.length)}`);
  console.log(`Ads: ${DosDecimales(CantidadAds, videos.length)}`);
  console.log(`SeoMostar: ${DosDecimales(CantidadSeoMostar, videos.length)}`);
  console.log(`Nuevo Sistema: ${DosDecimales(NuevoSistema, videos.length)}`);
}

(() => {
  console.log("💫 Generador de Description de Youtube 💫");
  writeDescriptions(getVideoData());
})();
