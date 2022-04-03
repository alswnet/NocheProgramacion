---
title: "Guia de Contribucion Comunitaria"
redirect_from:
  - "/tucodigo"
---

Agrega tu codigo a NocheProgramacion.com para que todo el mundo pueda aprender de el.

## ¡Aquí te lo dejo en Video por si te gusta más de esa forma!

[![Cómo agregar tu contribución](https://i3.ytimg.com/vi/nGAHSes_0Nk/hqdefault.jpg)](https://youtu.be/nGAHSes_0Nk)

[Cómo agregar tu contribución a la pagina NocheProgramacion](https://youtu.be/nGAHSes_0Nk)

---

Si deseas agregar tu propia versión o implementación o modificación de un Tutorial/Envivo/Curso/etc. en la pagina NocheProgramacion, simplemente agrega una referencia a tu código(repositorio) y/o ejemplo trabajando (Video/Gif/Foto/blog) correspondiente al que se quiere agregar tu versión.

Te recomendamos seguir los siquientes pasos:

## 0. Preparate

¡Genial! Que bueno que decidieras compartir tu trabajo con el mundo. Prepara tu implementación o modificación del Tutorial/Desafio/Envivo que haz seleccionado para compartir.

Para poder agregar tu código es necesario:

1. Una cuenta de Github es gratis, es como una red social pero de código.
2. Un lugar donde este subido tu código puede ser también en un repositorio de Github [(Como usar Github con Atom)]({{ site.baseurl }}{% link _tutoriales/056_Como_Usar_Git_y_Github_En_Windows_Facil.md %})
3. (Opcional) Una demostración del proyecto puede ser Video/Gif/OnLine/Articulo/Foto/post

## 1. Localizar

Dentro de la página de NocheProgramacion busca a cual quieres agregar tu contribución. Dentro de la sección de "Contribucion Comunitaria" encontraras un link **_tu propia versión_** el link te abrirá la página de Github para poder agregar tu contribución.

> **Tip: También puedes buscar Github**  
> Puedes encontrar también dentro de repositorio en github buscando dentro del folder que empieza con `_` como `_Tutorial` o `_Cusos` buscar el archivo .md y le das editar (icono del lápiz).

## 2. Agrega tu Contribución

Muy bien, !Ya estás en el lugar correcto! Bienvenido es la página del código que quieres agregar tu contribución, el codigo que ves es YAML ( el codigo que esta entre `---`), estan en un editor de texto web dentro de github, donde puedes agregar tu contribucción.

El código es similar a este que es el [Curso 7.1 de Introduccion a ML5]({{ site.baseurl }}{% link _Cursos/07_Inteligencia_Artificial_ML5/7.1-Introduccion-ML5.md %})

```markdown
---
title: "Introduccion ML5"
video_number: 1
date: 2019-04-04
video_id: IHTeKlIzO5M
repository: 07_Inteligencia_Artificial_ML5/07.1-Introduccion-Ml5

contributions:
  - title: "Demo Ml5 con Materialize y nuevas librerias"
    author:
      name: "ChepeCarlos"
      url: "http://chepecarlos.com"
    url: "https://alswnet.github.io/DemoML5/"
    source: "https://github.com/alswnet/DemoML5"
---

Hoy les ayudare como poder unir Python y arduino con el poder de MQTT
```

En este ya hay una contribucción debajo de `contributions`, para agregar la tuya debajo de la última contribucción aqui un código ejemplo para que la modifiques con tus datos.

```yaml
- title: "El titulo de tu versión (!Escoge uno genial!)"
  author:
    name: "Tu nombre (Se mostrara en la página)"
    url: "(Opcional) Link a tu página o cuenta social (Para que cuentren mas trabajo tuyo)"
  url: "Link de tu proyecto corriendo preferencia dentro del navegador o video o gif"
  source: "Link de tu código como un repositorio o pagina web donde se puede ver tu versión del código fuente"
```

si no esta lo puede agregar la sección poniendo al principio `contributions:` al final antes de `---`

```yaml
contributions:
  - title: "El titulo de tu versión (!Escoge uno genial!)"
    author:
      name: "Tu nombre (Se mostrara en la página)"
      url: "(Opcional) Link a tu página o cuenta social (Para que cuentren mas trabajo tuyo)"
    url: "Link de tu proyecto corriendo preferencia dentro del navegador o video o gif"
    source: "Link de tu código como un repositorio o pagina web donde se puede ver tu versión del código fuente"
```

Cuando estes felíz con lo que agregaste pasa al siquiente paso, intenta respetar los espacios y si hay otras contribuciones agrega la tuya al final de la lista.

## 3. Crea un Pull Request

El último paso es crear un Pull Request(Solicitud de agregar código). Simplemente presionas "Propose changes"(Propones cambios - Boton color verde) para crear una solicitud, que esta al final de la página. Complemente la información requerida (título y descripción).
Te mostrará la página para crear pull request presiona el botón "Create pull request". **Intente incluir un enlace a una demostración en ejecución** (o video / gif / captura de pantalla) en la descripción de la solicitud de extracción. ¡Esto hace que sea fácil ver rápidamente la contribución y proporcionar comentarios! También hay un lugar en la plantilla de Pull Request para incluir sus preferencias sobre su contribución compartida en las redes sociales de ALSW.

¡Eso es! Se le notificará tan pronto como un contribuyente con acceso de escritura a este repositorio haya revisado sus cambios.

¡Gracias por compartir tu trabajo con el mundo!
