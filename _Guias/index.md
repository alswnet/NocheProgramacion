---
title: "Guias"
---

Lista de Guia para contribuir con ALSW

{% assign guides = site.Guias | where_exp: 'guide', 'guide.url != page.url' %}
{% for guide in guides %}
  - [{{ guide.title }}]({{guide.url}})
{% endfor %}
