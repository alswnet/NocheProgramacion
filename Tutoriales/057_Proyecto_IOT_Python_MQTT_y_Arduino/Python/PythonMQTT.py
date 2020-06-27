import paho.mqtt.client as mqtt
import time

def ConectarMQTT(client, userdata, flags, rc):
    print("Conencando al Servidor - "+str(rc))
    MiMQTT.subscribe("Boton")

def MensajeMQTT(client, userdata, msg):
    print(f"Mensaje secreto: {msg.topic} - {str(msg.payload)}")

def EnviandoMQTT(client, obj, mid):
    print("Mesaje: " + str(mid))

def SubcribiendoMQTT(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def LogMQTT(client, obj, level, string):
    print(f"Log: {string}")

MiMQTT = mqtt.Client()
MiMQTT.on_connect = ConectarMQTT
MiMQTT.on_publish = EnviandoMQTT
MiMQTT.on_message = MensajeMQTT
MiMQTT.on_subscribe = SubcribiendoMQTT
MiMQTT.on_log = LogMQTT

MiMQTT.username_pw_set("ALSWSexy", "SubcribanseAALSWenYoutube")
MiMQTT.connect("broker.shiftr.io", 1883)

MiMQTT.publish("LED", "Apagar")
time.sleep(5)
MiMQTT.publish("LED", "Encender")

MiMQTT.loop_forever()
