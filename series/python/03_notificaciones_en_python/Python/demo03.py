# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

from os import path
from notifypy import Notify

notification = Notify()
notification.title = "Titulo"
notification.message = "Hola Mundo"
icono = "LogoALSW.png"
direcion = path.abspath(path.dirname(__file__))
notification.icon = path.join(direcion, icono)
notification.send()

