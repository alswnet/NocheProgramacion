# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

from notifypy import Notify

def Notificacion(mensaje):
    notification = Notify()
    notification.title = "ElGatoALSW"
    notification.message = mensaje
    notification.send()