const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");

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

function ObtenerDataVideo() {
  const Directorios = [
    "_Tutoriales",
    "_Cursos",
    "_series",
    "_shorts",
    "_RetoProgramacion",
    "_Grabaciones",
    "_invitados",
    "_mas/bodega",
  ];

  let Archivos = [];
  for (const dir of Directorios) {
    BuscarVideoRecursivamente(dir, Archivos);
  }

  const videos = [];

  for (const Archivo of Archivos) {
    const contenido = fs.readFileSync(`./${Archivo}`, "UTF8");
    const data = yaml.loadFront(contenido);
    videos.push({
      data: data,
    });
  }

  return videos;
}

function ReiniciarFolder(dir) {
  fs.readdirSync(dir).forEach((file) => {
    fs.unlinkSync(path.join(dir, file), (err) => {
      if (err) throw err;
    });
  });
}

function CrearPaginaTags(tag, cantidad) {
  let descripcion = `---\n`;
  descripcion += `layout: tag\n`;
  descripcion += `title: "#${tag}"\n`;
  descripcion += `subtitle: "videos sobre #${tag}"\n`;
  descripcion += `tag-name: ${tag}\n`;
  descripcion += `---\n`;

  fs.writeFileSync(`_tag/${tag}.md`, descripcion);
}

function CrearNubeTags(ListaTags) {
  let descripcion = `---\n`;
  descripcion += `layout: base\n`;
  descripcion += `title: "Nube de tags"\n`;
  descripcion += `redirect_from:\n`;
  descripcion += ` - /tag\n`;
  descripcion += `---\n\n`;

  descripcion += `<div class="link-list">\n`;
  descripcion += `\t<ul>\n`;

  ListaTags.forEach((tag) => {
    descripcion += `\t\t<li>\n`;
    descripcion += `\t\t\t<a href="/tag/${tag.nombre}">#${tag.nombre} [${tag.cantidad}]]</a>\n`;
    descripcion += `\t\t</li>\n`;
  });

  descripcion += `\t</ul>\n`;
  descripcion += `</div>\n`;

  fs.writeFileSync(`_tag/nube_tag.md`, descripcion);
}

function CrearTags(videos) {
  ReiniciarFolder("./_tag");

  let ListaTags = [];
  let VideosConTags = 0;

  for (let i = 0; i < videos.length; i++) {
    const data = videos[i].data;

    if (data.tags) {
      VideosConTags++;
      for (let i = 0; i < data.tags.length; ++i) {
        TagActual = data.tags[i];
        if (TagActual !== null) {
          TagActual = TagActual.toLowerCase();

          let ID = ListaTags.findIndex((i) => i.nombre === TagActual);

          if (ID >= 0) {
            ListaTags[ID].cantidad++;
          } else {
            let SuperTag = new Object();
            SuperTag.nombre = TagActual;
            SuperTag.cantidad = 1;
            ListaTags.push(SuperTag);
          }
        }
      }
    }
  }

  ListaTags = ListaTags.sort(function (a, b) {
    return b.cantidad - a.cantidad;
  });
  
  ListaTags.forEach((tag) => CrearPaginaTags(tag.nombre, tag.cantidad));
  CrearNubeTags(ListaTags);
  
  console.log(`Paginas de Tags: ${ListaTags.length} `);
  console.log(`Articulos con tags:  ${VideosConTags}`);
}

(() => {
  console.log("💫 Generador de Tags de NocheProgramacion 💫");
  CrearTags(ObtenerDataVideo());
})();
