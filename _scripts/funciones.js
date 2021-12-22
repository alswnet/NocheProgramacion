const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");

function ObtenerDataVideo() {
  const Directorios = [
    "_Tutoriales",
    "_Cursos",
    "_series",
    "_listas",
    "_shorts",
    "_RetoProgramacion",
    "_grabaciones",
    "_colaboraciones",
    "_mas/bodega",
    "_ponencias",
    "_extras",
  ];

  let Archivos = [];
  for (const dir of Directorios) {
    BuscarVideoRecursivamente(dir, Archivos);
  }

  const videos = [];

  for (const Archivo of Archivos) {
    const contenido = fs.readFileSync(`./${Archivo}`, "UTF8");
    const data = yaml.loadFront(contenido);
    let url = Archivo.substring(1);
    url = url.substring(0, url.length - 3);
    videos.push({
      pageURL: url,
      data: data,
      playlist: ObtenerPlatlist(Archivo),
      playlistName: ObtenerPlatlistNombre(Archivo),
    });
  }

  return videos;
}

function BuscarVideoRecursivamente(dir, arrayOfFiles) {
  const Archivos = fs.readdirSync(dir);

  arrayOfFiles = arrayOfFiles || [];

  for (const Archivo of Archivos) {
    if (fs.statSync(`${dir}/${Archivo}`).isDirectory()) {
      arrayOfFiles = BuscarVideoRecursivamente(
        `${dir}/${Archivo}`,
        arrayOfFiles
      );
    } else {
      if (Archivo !== "index.md" && Archivo.endsWith(".md")) {
        arrayOfFiles.push(path.join(dir, "/", Archivo));
      }
    }
  }

  return arrayOfFiles;
}

async function ReiniciarFolder(dir) {
  fs.readdirSync(dir).forEach((file) => {
    fs.unlinkSync(path.join(dir, file), (err) => {
      if (err) throw err;
    });
  });
}

function ObtenerPlatlist(file) {
  const series = file.substring(0, file.lastIndexOf("/")) + "/index.md";
  const content = fs.readFileSync(series);
  const parsed = yaml.loadFront(content);
  if (parsed.playlist_id) {
    return parsed.playlist_id;
  }
  return false;
}

function ObtenerPlatlistNombre(file) {
  const series = file.substring(0, file.lastIndexOf("/")) + "/index.md";
  const content = fs.readFileSync(series);
  const parsed = yaml.loadFront(content);
  if (parsed.title) {
    return parsed.title;
  }
  return false;
}

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

module.exports = {
  ObtenerDataVideo,
  BuscarVideoRecursivamente,
  ReiniciarFolder,
  ObtenerURLYoutube,
};
