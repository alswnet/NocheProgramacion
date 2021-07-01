# Creado ChepeCarlos de ALSW
# Tutorial Completo en https://nocheprogramacion.com
# Canal Youtube https://youtube.com/alswnet?sub_confirmation=1

import paho.mqtt.client as mqtt

client = mqtt.Client()
client.connect("test.mosquitto.org", 1883, 60)
client.publish("ALSW/temp", "99")
