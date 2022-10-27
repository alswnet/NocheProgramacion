const fs = require("fs");
const path = require("path");
const yaml = require("yaml-front-matter");
const {
  ObtenerDataVideo,
  BuscarVideoRecursivamente,
  ReiniciarFolder,
} = require("./funciones");

function CrearPaginaPresente(ListaPresentes) {
  let descripcion = `---\n`;
  descripcion += `layout: base\n`;
  descripcion += `title: "Nube de tags"\n`;
  descripcion += `redirect_from:\n`;
  descripcion += ` - /tag\n`;
  descripcion += `---\n\n`;

  descripcion += `<div class="link-list">\n`;
  descripcion += `\t<ul>\n`;

  ListaPresentes.forEach((tag) => {
    descripcion += `\t\t<li>\n`;
    descripcion += `\t\t\t<a href="https://www.youtube.com/channel/${tag.canal}">#${tag.nombre} [${tag.cantidad}]</a>\n`;
    descripcion += `\t\t</li>\n`;
  });

  descripcion += `\t</ul>\n`;
  descripcion += `</div>\n`;

  fs.writeFileSync(`_Guias/presente.md`, descripcion);
}

async function CrearTableroPresente(videos) {
  let ListaPresentes = [];
  for (let i = 0; i < videos.length; i++) {
    const data = videos[i].data;
    if (data.asistencia) {
      for (let i = 0; i < data.asistencia.length; ++i) {
        asistenteActual = data.asistencia[i].canal;
        let ID = ListaPresentes.findIndex((i) => i.canal === asistenteActual);

        if (ID >= 0) {
          ListaPresentes[ID].cantidad++;
        } else {
          let PresenteActual = new Object();
          PresenteActual.canal = asistenteActual;
          PresenteActual.nombre = data.asistencia[i].title;
          PresenteActual.cantidad = 1;
          ListaPresentes.push(PresenteActual);
        }
      }
    }
  }

  ListaPresentes = ListaPresentes.sort(function (a, b) {
    return b.cantidad - a.cantidad;
  });

  console.log(ListaPresentes);

  CrearPaginaPresente(ListaPresentes);
}

(() => {
  console.log("💫 Generador de asistentes a EnVivo de NocheProgramacion 💫");
  CrearTableroPresente(ObtenerDataVideo());
})();
