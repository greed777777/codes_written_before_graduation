import paho.mqtt.client as mqtt
import json


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("connected OK")
    else:
        print("Bad connection Returned code=", rc)


def on_disconnect(client, userdata, flags, rc=0):
    print(str(rc))


def on_publish(client, userdata, mid):
    print("In on_pub callback mid= ", mid)


# ??? ????? ??
client = mqtt.Client()
# ?? ?? ?? on_connect(???? ??), on_disconnect(???? ????), on_publish(??? ??)
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_publish = on_publish
# address : localhost, port: 1883 ? ??
client.connect('localhost', 1883)
client.loop_start()
# common topic ?? ??? ??
client.publish('common', "hello, from RPI", 1)
client.loop_stop()
# ?? ??
client.disconnect()
