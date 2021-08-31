# NocheProgramacion

Sitio web de Tutoriales y Seria video de **ALSW**

# Codigo Pagina Web

El codigo del Sitio Web esta Basado en el trabajo de La comunidad de [The Coding Train](https://github.com/CodingTrain) y [shiffman](https://shiffman.net/) miembro junta directores [Processing Foundation](https://processing.org/) y Profesor en [Escuela de Artes Tisch de la Universidad de Nueva York](https://tisch.nyu.edu/).

Este Sitio Web es [Fork](https://en.wikipedia.org/wiki/Fork_(software_development)) del Sitio Web de [TheCodingTrain](https://thecodingtrain.com/) que se refiere que tomamos el codigo de base y lo adaptamos a las necesidades de ALSW si te gussta lo que hacemos ve al canal de Youtube de [The Coding Train](https://www.youtube.com/user/shiffman)

Repositorio de Github: [The Coding Train](https://github.com/CodingTrain/website)

# Atributos Base de un Articulo (.md)

La información básica de los artículos para generar [pagina web](https://nocheprogramacion.com/series/mqtt/001_Que_es_MQTT.html) y [Descripcion Youtube](https://www.youtube.com/watch?v=T1_w8-8Y5kc)

| Dato                                 | Etiqueta       | Ejemplo                 | Opcional |
| ------------------------------------ | -------------- | ----------------------- | -------- |
| Titulo                               | title          | Que es MQTT             |          |
| Id Interno                           | video_number   | 1                       |          |
| Fecha (Formato USA)                  | date           | 2021-03-23              |          |
| ID de Youtube                        | video_id       | T1_w8-8Y5kc             |          |
| Codigos y/o Diagramas                | repository     | mqtt/002_MQTT_en_Nodejs | True     |
| Tags                                 | tags           | - mqtt - nodejs   - iot | True     |
| Id Interno Curso                     | course_number  | 1                       | True     |
| Agregar a generador de descripciones | actualizado    | true o false            | True     |
| Puede subir sus propias verciones    | can_contribute | false                   | True     |

# Reconoce Automáticamente Código

Para agregar codigo a un articulo debe estas folder definido en **repository**

| Tipo Codigo | Nombre Folder |
| ----------- | ------------- |
| Arduino     | Arduino       |
| Python      | Python        |
| P5.js       | P5            |
| Processing  | Processing    |
| Node.js     | Node          |
| Diagrama    | Diagrama      |
| Pagina web  | HTML          |
| JavaScript  | JavaScript    |

## Informacion video

title: "String"
video_number: numbre
date: 1988-07-17
video_id: String
can_contribute: boolean
repository: boolean

## Lista de Atributos de Articulo

| Tipo Atributo           | Categoria       |
| ----------------------- | --------------- |
| Link Referencia         | links           |
| Otro contenidos de ALSW | videos          |
| Circuitos               | piezas          |
| Heramientas             | tools           |
| Libros                  | books           |
| Personalizados          | custom_sections |

### Valores cada elemento de una lista

| Datos  | Etiqueta | Ejemplo             | Opcional |
| ------ | -------- | ------------------- | -------- |
| Titulo | title    | Pagina de MQTT      |          |
| Link   | url      | <https://mqtt.org/> | true     |

| Indice del Video   | topics    |

-   parts
-   links
-   piezas
-   books
-   videos
-   tools

## Informacion de Links

-   title string  > Titulo del link
-   video_id string > ID video Youtube
-   playlist_id string > ID Playlist Youtubr
-   url string > Link a pagina Externa
-   author[.name] string|Author > Nombre usuario
-   author.url string > URL del Autor
-   source string  > URL base del codigo donde se encontro el link
-   pieza string > ID producto de a ALSW

## Sexion Extra

custom_sections:

-   title: "Mombre Senccion"
    items:
    -   title: "Twitter"
        url: "<https://twitter.com/ALSW>"
    -   title: "Pwebsite"
        url: "<http://www.alsw.net>

## Ejemplo

links:

-   title: "Libreria de Sensor Capacitivo"
    url: "<https://playground.arduino.cc/Main/CapacitiveSensor/>"

# Link Sociales

Alguno enlaces que puede ser del interes para mantener contacto con nosotros:

-   [Youtube](http://youtube.com/alswnet)
-   [Discord](https://nocheprogramacion.com/discord)
-   [Donar Cafe](https://www.buymeacoffee.com/alswnet)
-   [Patreon](http://patreon.com/alswnet)
-   [Instagram](https://www.instagram.com/alswnet)
-   [Twitter](https://twitter.com/alswnet)
-   [Facebook](http://facebook.com/alswnet)
-   [Grupo ChepeCarlosClub](http://www.facebook.com/groups/chepecarlosclub/)

## Prueva Servidor

[Instalacion Jekyll](https://jekyllrb.com/docs/installation/#requirements)

```bash
$ bundle exec jekyll serve
```

# Horario NocheProgramacion

Son todos lo Viernes  se Trasmite "NocheProgramacion" a 7:00 pm ( UTC-6 ) hora de San Salvador, El Salvador.
[Puedes usar esta Calculadora para encontrar la hora de tu pais](https://www.thetimezoneconverter.com/?t=7%3A00%20pm&tz=El%20Salvador&)

# Contribuidores

-   [ChepeCarlos](https://github.com/chepecarlos) (chepecarlos@alswblog.org)
-   [Evorock](https://github.com/evorock) (Evorock@alswblog.org)
-   [Car0sHdz](https://github.com/carl0shdz) (carlitos.hernandez203@gmail.com)
-   [Dennnnys](https://github.com/dennnnys) (denisaragon60@gmail.com)
-   [Ferbrod](https://github.com/Ferbrod)(fercho200118303@gmail.com)
-   [EdwinAlmira](https://github.com/EdwinAlmira)(ealopezalmira@gmail.com)
-   [OtmaroMiguel](https://github.com/Otmaromiguel)(otmaromiguel4@gmail.com)
