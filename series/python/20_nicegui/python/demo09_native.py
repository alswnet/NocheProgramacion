from nicegui import ui

ui.button('Suscribirse', on_click=lambda: ui.notify('Suscríbete a ChepeCarlos en Youtube!'))

ui.run(native=True)