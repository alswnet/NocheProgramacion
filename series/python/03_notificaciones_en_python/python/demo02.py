# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

from notifypy import Notify

notification = Notify()
notification.title = "Titulo"
notification.message = "Hola Mundo"
notification.icon = "/home/chepecarlos/1.Proyectos/1.Oficiales/1.NocheProgramacion/series/python/03_notificaciones_en_python/Python/LogoALSW.png"

notification.send()
