---
title: "Links de ALSW"
redirect_from:
  - "/links"
  - "/link"
---

### Ultimo Video

{% include 1-tools/all-tutorial.html %}

{% include 1-tools/sort-videos.html videos=all_Videos sortByDate=true reverse=true %}
{% assign TodosVideos = out_sortedVideos %}

{% assign Ultimo = TodosVideos | first %}

<div class="video-card">
    <a href="https://youtu.be/{{ Ultimo.video_id }}">
        <div class="video-header">
            <div class="thumb-container">
                <div class="video-thumbnail"
                    {% if Ultimo.video_id %}
                    style="background-image: url(https://i.ytimg.com/vi/{{Ultimo.video_id}}/mqdefault.jpg)"
                    {% else %}
                    style="background-image: url({{ '/assets/images/streamcover.jpg' | relative_url }})"
                    {% endif %}
                >
                </div>
            </div>

           <h3>{{ Ultimo.title | xml_escape }}</h3>

            {% if Ultimo.date > site.time %}
                <span class="video-date">{{ Ultimo.date | date: '%d %b %Y - %H:%M %Z' }}</span>
            {% else %}
                <span class="video-date">{{ Ultimo.date | date_to_string }}</span>
            {% endif %}
        </div>
    </a>

    <div class="buttons">
        <a href="https://youtu.be/{{ Ultimo.video_id }}" aria-label="Youtube">
            YouTube
        </a>
    </div>
</div>

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
