---
title: "Guia de Contribucion Comunitaria"
---

## ¡Aquí te lo dejo en Video por si te gusta mas de esa forma!

[![Cómo agregar tu contribución](http://i3.ytimg.com/vi/9BZzxlyFfHM/hqdefault.jpg)](https://youtu.be/9BZzxlyFfHM)

[Cómo agregar tu contribución a la pagina NocheProgramacion](https://youtu.be/9BZzxlyFfHM)

---

Si deseas agregar tu propia vercion o implementacion o modificacion de un Tutorial/Envivo/Curso/etc. en la pagina NocheProgramacion, simplemente agrega una referencia a tu codigo(repositorio) y/o ejemplo trabajando (Video/Gif/Foto/blog) correspondiente al que quiere agregar tu vercion  

Te recomendamos que sigan los siquientes pasos:

## 0. Preparate

¡Genial! Que bueno que decidieras compartir tu trabajo con el mundo. Prepara tu implementacion o modificacion del Tutorial/Desafio/Envivo que has selecionado para compartir.

Para poder agregar tu codigo es necesarios:

1. Una cuenta de Github es gratis, es como una red social pero de codigo
2. Un lugar donde tengas suvido tu codigo puede ser tambien en un repositorio de Github [(Como usar Github con Atom)]({{ site.baseurl }}{% link _Tutoriales/058_Como_Usar_Git_y_Github_En_Windows_Facil.md %})
3. (Opcional) Una demostracion del proyecto puede se Video/Gif/OnLine/Articulo/Foto/post


## 1. Localizar

Dentro de la pagina de NocheProgramacion busca cual quieres agregar tu contribucion. Dentro de la seccion de "Contribucion Comunitaria" encontraras un link ***tu propia vercion***, el link te abrira la pagina de Github para poder agregar tu contribucion.

> **Tip: Tambien puede buscar Github**  
> Puedes encontrar tambien dentro de repositorio en github buscando dentro del folde que empieza con `_` como `_Tutorial` o `_Cusos` buscar el archivo .md y le das editar icono del lapiz

## 2. Agrega tu Contribucion

Muy bien, !Ya estas en el lugar correcto! bienbenido es la pagina de codigo que quieres agregar tu contribucion, el codigo que ves es YAML ( el codigo que esta entre `---`), estan en un editor de texto web dentro de github, donde puede agregar tu contribuccion.  

El codigo es similar a este que es el tutorial numero 57 el de Python, MQTT y Arduino

``` markdown
---
title: "Proyecto IOT: Python, MQTT y Arduino"
video_number: 57
date: 2020-05-17
video_id: LSrDIklFiJ8
repository: 057_Proyecto_IOT_Python_MQTT_y_Arduino

contributions:
  - title: "Enviando coneccion local MQTT"
    author:
      name: "ChepeCarlos"
      url: "http://chepecarlos.com"
    url: "https://codingtrain.github.io/Rainbow-Code"
    source: "https://github.com/codingtrain/Rainbow-Code"
---

Hoy les ayudare como poder unir Python y arduino con el poder de MQTT
```

Es este ya hay una contribuccion debajo de `contributions`, para agregar la tuya debajo de la ultima contribuccion aqui un codigo ejemplo para que la modifiques con tus datos

``` yaml
  - title: "El titulo de tu vercion (!Escojege uno genial!)"
    author:
      name: "Tu nombre (Se mostrara en la pagina)"
      url: "(Opcional) Link a tu pagina o cuenta social (Para que cuentren mas trabajo tuyo)"
      url: "Link de tu proyecto corriendo preferencia dentro del navegador o video o gif"
      source: "Link de tu codigo como un repositrio o paginaweb donde se puede ver tu vercion del codigo fuente"
```

si no esta lo puede agregar la seccion poniendo al principio `contributions:` al final antes de `---`

``` yaml
contributions:
  - title: "El titulo de tu vercion (!Escojege uno genial!)"
    author:
      name: "Tu nombre (Se mostrara en la pagina)"
      url: "(Opcional) Link a tu pagina o cuenta social (Para que cuentren mas trabajo tuyo)"
    url: "Link de tu proyecto corriendo preferencia dentro del navegador o video o gif"
    source: "Link de tu codigo como un repositrio o paginaweb donde se puede ver tu vercion del codigo fuente"
```

Cuando estes feliz con lo que agregaste pasa al siquiente paso, intenta respetar los espacios y si hay otra contribuciones agrega la tuya a la final de la lista  

## 3. Crea un Pull Request

El último paso es crear un Pull Request(Solisitud de agregar codigo). Simplemente precionas "Propose changes"(Propones cambios - Boton color verdad) para crear una solicitud, que esta al final de la pagina. Complete la información requerida (título y descripción).
Te mostrara la pagina para crear pull request precional el boton "Create pull request". **Intente incluir un enlace a una demostración en ejecución** (o video / gif / captura de pantalla) en la descripción de la solicitud de extracción. ¡Esto hace que sea fácil ver rápidamente la contribución y proporcionar comentarios! También hay un lugar en la plantilla de Pull Request para incluir sus preferencias sobre su contribución compartida en las redes sociales de ALSW.

¡Eso es! Se le notificará tan pronto como un contribuyente con acceso de escritura a este repositorio haya revisado sus cambios.

¡Gracias por compartir tu trabajo con el mundo!
