const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");

// TODO: Tags a miniscuas por defecto

function BuscarVideoRecursivamente(dir, arrayOfFiles) {
  const files = fs.readdirSync(dir);

  arrayOfFiles = arrayOfFiles || [];

  for (const file of files) {
    if (fs.statSync(`${dir}/${file}`).isDirectory()) {
      arrayOfFiles = BuscarVideoRecursivamente(`${dir}/${file}`, arrayOfFiles);
    } else {
      if (file !== "index.md" && file.endsWith(".md")) {
        arrayOfFiles.push(path.join(dir, "/", file));
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

  let files = [];
  for (const dir of Directorios) {
    BuscarVideoRecursivamente(dir, files);
  }

  const videos = [];

  for (const file of files) {
    const content = fs.readFileSync(`./${file}`, "UTF8");
    const parsed = yaml.loadFront(content);
    videos.push({
      data: parsed,
    });
  }

  return videos;
}

function primeDirectory(dir) {
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

function CrearNubeTags(tags, cantidad) {
  let descripcion = `---\n`;
  descripcion += `layout: base\n`;
  descripcion += `title: "Nube de tags"\n`;
  descripcion += `redirect_from:\n`;
  descripcion += ` - /tag\n`;
  descripcion += `---\n\n`;

  descripcion += `<div class="link-list">\n`;
  descripcion += `\t<ul>\n`;

  for (let i = 0; i < tags.length; i++) {
    descripcion += `\t\t<li>\n`;
    descripcion += `\t\t\t<a href="/tag/${tags[i]}">#${tags[i]} [${cantidad[i]}]]</a>\n`;
    descripcion += `\t\t</li>\n`;
  }

  descripcion += `\t</ul>\n`;
  descripcion += `</div>\n`;

  fs.writeFileSync(`_tag/nube_tag.md`, descripcion);
}

function CrearTags(videos) {
  primeDirectory("./_tag");

  let tags = [];
  let cantidad = [];
  for (let i = 0; i < videos.length; i++) {
    const data = videos[i].data;

    if (data.tags) {
      for (let i = 0; i < data.tags.length; ++i) {
        TagActual = data.tags[i];
        if (TagActual !== null) {
          TagActual = TagActual.toLowerCase();
          if (!tags.includes(TagActual)) {
            tags.push(TagActual);
            cantidad.push(1);
          } else {
            indice = tags.indexOf(TagActual);
            cantidad[indice] += 1;
          }
        }
      }
    }
  }

  for (let i = 0; i < tags.length; i++) {
    CrearPaginaTags(tags[i], cantidad[i]);
  }
  CrearNubeTags(tags, cantidad);
  console.log("Cantidad Paginas de tags " + tags.length);
}

(() => {
  console.log("💫 Generador de Tags 💫");
  CrearTags(ObtenerDataVideo());
})();
