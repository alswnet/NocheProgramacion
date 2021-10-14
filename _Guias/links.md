---
title: "Links de ALSW"
redirect_from:
  - "/links"
  - "/link"
---

### Ultimo Video

{% include 1-tools/sort-videos.html videos=site.shorts %}
{% assign TodosVideos = out_sortedVideos %}

{% include 1-tools/sort-videos.html videos=site.Tutoriales %}
{% for video in out_sortedVideos %}
    {% assign TodosVideos = TodosVideos | push: video %}
{% endfor %}

{% include 1-tools/sort-videos.html videos=site.series %}
{% for video in out_sortedVideos %}
    {% assign TodosVideos = TodosVideos | push: video %}
{% endfor %}

{% include 1-tools/sort-videos.html videos=site.mas %}
{% for video in out_sortedVideos %}
    {% assign TodosVideos = TodosVideos | push: video %}
{% endfor %}

{% include 1-tools/sort-videos.html videos=site.invitados %}
{% for video in out_sortedVideos %}
    {% assign TodosVideos = TodosVideos | push: video %}
{% endfor %}

{% include 1-tools/sort-videos.html videos=TodosVideos sortByDate=true reverse=true %}
{% assign TodosVideos = out_sortedVideos %}

{% assign Ultimo = TodosVideos | first %}

[{{ Ultimo.title | upcase }}](https://www.youtube.com/watch?v={{ Ultimo.video_id }})

### Youtube

[youtube.com/alswnet](https://www.youtube.com/alswnet?sub_confirmation=1)

### Instagram

[instagram.com/alswnet](https://www.instagram.com/alswnet/)

### Twitch

[twitch.tv/alswnet](https://www.twitch.tv/alswnet)

### Tutoriales

[nocheprogramacion.com](https://nocheprogramacion.com/)

### Discord

[nocheprogramacion.com/discord](https://nocheprogramacion.com/discord)

### Twitter

[twitter.com/alswnet](https://twitter.com/alswnet)

### Facebook

[facebook.com/alswnet](https://www.facebook.com/alswnet)

### Canal Juegos

[youtube.com/alsw2game](https://www.youtube.com/channel/UC-QPTA-oIQf59SVA8ckpMXA?sub_confirmation=1)

### Membresia

[youtube.com/alswnet/join](https://www.youtube.com/alswnet/join)

### Donacion

[buymeacoffee.com/alswnet](https://nocheprogramacion.com/cafe)
