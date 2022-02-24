---
title: Avances Exclusivo para Miembros
subtitle: Miralos antes que en YouTube
redirect_from:
  - "/miembros"

miembros:
  - title: Maker_Uno
    items:
      - title: Manuel Alegría
      - title: Lolailo Aviles Arroyo
      - title: jose Santos
      - title: Victoria Becerril
      - title: Erebos Ubuntu

nopublicidad: true
---

Miembros, **Que es Miembros**? Miembros es la forma de apoyar a tus creadores favoritos en YouTube. Donde donas una cantidad de Dinero mensual para permitir, mantener el motor vivo del canal. Con tu apoyo y de la comunidad, Crearemos mucho **Juntos**, [Únete YA](https://www.youtube.com/alswnet/join)

## Beneficios de Miembros

Estos son algunos:

- Avances exclusivos de Video
- Comando exclusivos con el BOT_ALSW
- Tu nombre en la descripción de los videos
- Insignia Especial junto al nombre en Canal de YouTube de ChepeCarlos
- Emoji Extras en EnVivos de Canal de YouTube de ChepeCarlos
- Acceso a Rol y Sala para miembros en Discord de ALSW
- Voz y voto del rumbo del contenido del Canal
- Muchas cosas mas como avances de Proyectos
- Mi agradecimiento y aprecio 😉

<p style="display: flex; justify-content: center;"> 
  <a href="https://www.youtube.com/alswnet/join">
    <img style="max-width: 25rem;" alt="Miembro YouTube de ChepeCarlos" src="/assets/images/miembro_youtube.png">
  </a>
</p>

## Lista videos Exclusivos

> **Nuevos video todas las semanas**
>
> Se agregaran los videos cuando estén listos.  
> Serán públicos en el futuro para toda la comunidad

{% assign video_miembros = '' | split: '' %}

{% include 1-tools/all-tutorial.html %}

{% for video in all_Videos %}
{% if video.para_miembros %}
{% assign video_miembros = video_miembros | push: video %}
{% endif %}
{% endfor %}

{% include 3-modules/video-list.html sortedVideos=video_miembros nopublicidad=true %}

# Gracias a Miembros

{% comment %} Listas de MiembrosCustom link lists. {% endcomment %}
{% for section in page.miembros %}
{% include 3-modules/link-list.html links=section.items title=section.title class=section.class %}
{% endfor %}

# Unete YA

<p style="display: flex; justify-content: center;"> 
  <a href="https://www.youtube.com/alswnet/join">
    <img alt="Video Explicando Miembro YouTube de ChepeCarlos" src="https://i3.ytimg.com/vi/OkeQj6m_FZ8/mqdefault.jpg">
  </a>
</p>

<p style="display: flex; justify-content: center;"> 
  <a href="https://www.youtube.com/alswnet/join">
    <img style="max-width: 25rem;"  alt="Miembro YouTube de ChepeCarlos" src="/assets/images/miembro_youtube.png">
  </a>
</p>
