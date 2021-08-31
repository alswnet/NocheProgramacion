const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");
const {
  ObtenerDataVideo,
  BuscarVideoRecursivamente,
  ReiniciarFolder,
} = require("./funciones");

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

async function CrearTags(videos) {
  await ReiniciarFolder("./_tag");

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
