import threading

from obswebsocket import events, obsws, requests

class MiOBS:
    """Concepción con OBS."""

    def __init__(self, data):
        """Crea confección básica con OBS Websocket."""
        self.Reiniciar()

        if "servidor" in data:
            self.host = data["servidor"]
        if "puerto" in data:
            self.port = data["puerto"]
        if "contrasenna" in data:
            self.password = data["contrasenna"]
        if "topic" in data:
            self.topic = data["topic"]
        print(f"OBS[Iniciando] - {self.host}")
    
    def Reiniciar(self):
        self.host = "localhost"
        self.port = 4444
        self.topic = None
        self.password = None
        self.Conectado = False
        self.Notificar = None

    def Conectar(self):
        """Se conecta a OBS Websocket y inicializa los eventos."""

        try:
            print("OBS[Intentando conectar]")
            if self.password is None:
                self.OBS = obsws(self.host, self.port)
            else:
                self.OBS = obsws(self.host, self.port, self.password)

            self.OBS.connect()
            self.Conectado = True
            print(f"OBS[Conectado] {self.host}")
            self.Notificar(self.topic, "OBS-CONECTADO")
        except Exception as error:
            print(f"OBS[Error] {error}")
            self.Conectado = False
            self.Notificar(self.topic, "OBS-No-Conectado")
            return
       
        self.OBS.register(self.EventoEscena, events.SwitchScenes)
        self.OBS.register(self.EventoGrabando, events.RecordingStarted)
        self.OBS.register(self.EventoGrabando, events.RecordingStopping)
        self.OBS.register(self.EventoEnVivo, events.StreamStarted)
        self.OBS.register(self.EventoEnVivo, events.StreamStopping)
        self.OBS.register(self.EventoSalir, events.Exiting)

    def EventoGrabando(self, Mensaje):
        """Recibe estado de grabación."""
        if Mensaje.name == "RecordingStarted":
            print("OBS[Grabando]")
            self.Notificar(self.topic, "OBS-Grabando")
        elif Mensaje.name == "RecordingStopping":
            print(f"OBS[Grabo] {Mensaje.datain['rec-timecode']}")
            self.Notificar(self.topic, "OBS-No-Grabando")

    def EventoEnVivo(self, Mensaje):
        """Recibe estado del Striming."""
        if Mensaje.name == "StreamStarted":
            print("OBS[EnVivo]")
            self.Notificar(self.topic, "OBS-EnVivo")
        elif Mensaje.name == "StreamStopping":
            print(f"OBS[Paro EnVivo] {Mensaje.datain['stream-timecode']}")
            self.Notificar(self.topic, "OBS-No-EnVivo")
    
    def EventoSalir(self, Mensaje):
        """Recibe desconeccion de OBS websocket."""
        print("OBS[Desconecto OBS]")
        self.Conectado = False
        self.Notificar(self.topic, "OBS-No-Conectado")

    def EventoEscena(self, Mensaje):
        """Recibe nueva escena actual."""
        EscenaActual = Mensaje.datain["scene-name"]
        print(f"OBS[Escena] {EscenaActual}")
    
    def CambiarGrabacion(self):
        """Envia solisitud de cambiar estado de Grabacion."""
        if self.Conectado:
            print("Cambiando[Grabacion]")
            self.OBS.call(requests.StartStopRecording())
        else:
            print("OBS no Conectado")
            self.Notificar(self.topic, "OBS-No-Conectado")

    def CambiarEnVivo(self):
        """Envia solisitud de cambiar estado del Streaming ."""
        if self.Conectado:
            print("Cambiando estado EnVivo")
            self.OBS.call(requests.StartStopStreaming())
        else:
            print("OBS no Conectado")
            self.Notificar(self.topic, "OBS No Conectado")
