from nicegui import ui

columns = [
    {'name': 'Nombre', 'label': 'Nombre', 'field': 'nombre', 'required': True, 'align': 'left'},
    {'name': 'Edad', 'label': 'Edad', 'field': 'edad', 'sortable': True},
]
rows = [
    {'nombre': 'Carlos', 'edad': 34},
    {'nombre': 'Paty', 'edad': 25},
    {'nombre': 'ingJuan'},
]
ui.table(columns=columns, rows=rows, row_key='nombre')

ui.run()