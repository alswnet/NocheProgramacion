---
layout: base
title: Colaboradores
redirect_from:
  - /colaboradores
---

ALSW es creado gracias a:
<ul>
  {% for colaborador in site.colaboradores %}
    {% if colaborador.colaborador_id %}
    <li>
      <a href="{{ colaborador.url }}" >#{{colaborador.colaborador_id }} | {{colaborador.title}} | {{ colaborador.nombre }}</a>
    </li>
    {% endif %}
  {% endfor %}
</ul>
