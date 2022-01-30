---
title: Avances Exclusivo para Miembros
subtitle: Miralos antes que en Youtube
redirect_from:
  - "/miembros"

miembros:
  - title: Maker_Uno
    items:
      - title: Victoria Becerril
      - title: Erebos Ubuntu

nopublicidad: true
---

Miembros, **Que es Miembros**? Miembros es la forma de apoyar a tus creadores favoritos en Youtube. Donde donas una cantidad de Dinero mensual para permitir, mantener el motor vivo del canal. Con tu apoyo y de la comunidad, Crearemos mucho **Juntos**, [Unete YA](https://www.youtube.com/alswnet/join) 

## Beneficios de Miembros

Estos son algunos:

- Avances exclusivos de Video
- Comando exclusivos con el BOT_ALSW
- Tu nombre en la descripcion de los videos
- Insignia Especial justo a nombre en Canal de Youtube de ChepeCarlos
- Emoji Extras en EnVivos de Canal de Youtube de ChepeCarlos
- Acceso a Rol y Sala para miembros en Discord de ALSW
- Voz y voto del runbo del contenido del Canal
- Muchas cosas mas como avances de Proyectos
- Mi agradecimiento y aprecio 😘

<p style="display: flex; justify-content: center;"> 
  <a href="https://www.youtube.com/alswnet/join">
    <img style="max-width: 25rem;" alt="Miembro Youtube de ChepeCarlos" src="/assets/images/miembro_youtube.png">
  </a>
</p>

## Lista videos Exclusivos

> **Nuevos video todas las semanas**
> 
> Se agregan los video cuando esten lintos, gracias por el apoyo.  
> Seran publico en el futuro para toda la comunidad

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
    <img alt="Video Explicando Miembro Youtube de ChepeCarlos" src="https://i3.ytimg.com/vi/nGAHSes_0Nk/mqdefault.jpg">
  </a>
</p>

<p style="display: flex; justify-content: center;"> 
  <a href="https://www.youtube.com/alswnet/join">
    <img style="max-width: 25rem;"  alt="Miembro Youtube de ChepeCarlos" src="/assets/images/miembro_youtube.png">
  </a>
</p>


