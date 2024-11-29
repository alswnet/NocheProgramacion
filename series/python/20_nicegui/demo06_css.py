from nicegui import ui
# css https://tailwindcss.com/
# iconos https://fonts.google.com/icons

ui.label("Tecla").style("font-weight: bold")

ui.label("Como estas hoy").style("width: 125px").classes("rounded-lg p-2 border-4 border-teal-600")

ui.button(icon='thumb_up', color="teal-300")

ui.run()