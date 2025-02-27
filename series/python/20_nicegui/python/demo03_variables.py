from nicegui import ui

texto = ui.label('Mensaje Secreto')

def mensajeTiktok():
    texto.text = "Síguenos en Tiktok"

def mensajeDos():
    texto.text = "Hola, como estas"

with ui.button_group():
    ui.button('Mensaje 1', on_click=mensajeTiktok)
    ui.button('Mensaje 2', on_click=mensajeDos)

ui.run()
