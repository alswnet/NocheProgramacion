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

function AgregarSeoMostar(descripcion, Cantidad, Actualizar) {
  let Lineas = descripcion.split(/\n/);
  let LongitudLinea = 90;
  if (descripcion.length <= LongitudLinea * 2 && Lineas.length <= 2) {
    descripcion += `👇 👇 HAZ CLICK 👇 👇\n`;
    if (Actualizar) Cantidad.SeoMostarActivo++;
    Cantidad.SeoMostar++;
  } else if (Lineas[0].length <= LongitudLinea * 2) {
    let D = Lineas[0];
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

async function CrearDescripciones(videos) {
  let CantidadVideos = videos.length;
  let ActivadoAdsGlobal = false;
  let Cantidad = new Object();
  Cantidad.Facebook = 0;
  Cantidad.Ads = 0;
  Cantidad.Video = 0;
  Cantidad.NuevoSistema = 0;

  await ReiniciarFolder("./descripciones-fb");
  // await ReiniciarFolder("./actualizado");

  for (let i = 0; i < videos.length; i++) {
    const data = videos[i].data;
    const pageURL = videos[i].pageURL;
    const playlist = videos[i].playlist;

    if (data.post_id) {
      Cantidad.Facebook++;
      let descripcion = "";

      // Descripcion
      let content = data.__content.trim();
      descripcion += `${content}\n`;

      // Todo: Actualizar seo mostrar para facebook
      // descripcion = AgregarSeoMostar(descripcion, Cantidad, data.actualizado);

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
        Cantidad.Ads++;
        for (let i = 0; i < data.ads.length; ++i) {
          descripcion += `\n${data.ads[i].title} ${data.ads[i].url}\n`;
        }
      }

      descripcion += `\n👇 👇 👇`;
      descripcion += "\nMira video en Youtube: ";
      descripcion += ObtenerURLYoutube(pageURL);

      // if (data.tags) {
      //   descripcion += `\n\n#ALSW`;
      //   for (let i = 0; i < data.tags.length; ++i) {
      //     descripcion += ` #` + data.tags[i];
      //   }
      //   // descripcion += `\n`;
      // }

      // descripcion += `\nEsta descripción fue auto-generada. Si ves algún problema, por favor reportarlo en https://github.com/alswnet/NocheProgramacion/issues/new`;

      if (data.actualizado) {
        Cantidad.NuevoSistema++;
        fs.writeFileSync(`descripciones-fb/${data.post_id}.txt`, descripcion);
      }
    }
  }
  console.log(`Cantidad total videos: ${CantidadVideos}`);
  ImprimirData("Facebook", Cantidad.Facebook, CantidadVideos);
  ImprimirData("Ads", Cantidad.Ads, Cantidad.Facebook);
  ImprimirData("Nuevo Sistema", Cantidad.NuevoSistema, Cantidad.Facebook);
  console.log(`Ads Global: ${ActivadoAdsGlobal}`);
}

(() => {
  console.log(
    "💫 Generador de descripcion de NocheProgramacion para Facebook 💫"
  );
  CrearDescripciones(ObtenerDataVideo());
})();
