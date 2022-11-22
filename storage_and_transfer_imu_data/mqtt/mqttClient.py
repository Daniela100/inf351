# Source code to MQTT client: https://www.emqx.com/en/blog/how-to-use-mqtt-in-python

import paho.mqtt.client as mqtt
import time, os
from random import randint
from datetime import datetime
import csv

mqttBroker ="mqtt.m5stack.com"
clientID = "PC" + str(randint(0, 1000000))
topic = "IMUTRANSFER"
tcpPort = 1883

flagConnection = 0

data = ''

def publish(client, msg, topic):
    while True:
        result = client.publish(topic, msg)

        if result[0] == 0:
            print(f"Publish [{topic}]: {msg}")
            break
        else:
            time.sleep(1)

def on_message(client, userdata, message):
    msg = str(message.payload.decode("utf-8"))
    global data 
    data += msg
    print("received message: " , msg)

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
        global flagConnection
        flagConnection = 1
    else:
        print("Failed to connect, return code {}".format(rc))

def connect_mqtt(clientID, broker, port):
    client = mqtt.Client(clientID)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client



if not os.path.exists("IMU_DATA"):
    os.mkdir("IMU_DATA")

client = connect_mqtt(clientID, mqttBroker, tcpPort)
client.connect(mqttBroker)

# client.loop_forever()
client.loop_start()
publish(client, "S", topic)

client.subscribe("IMUTRANSFER")
client.on_message=on_message 

time.sleep(65)
client.loop_stop()
client.disconnect()

print("Tempo de envio esgotado")

print("\n\nARMAZENANDO DADOS EM 'IMU_DATA/", end='')
if len(data) > 0:
    now = datetime.now()
    formatNow = now.strftime("%d-%m-%Y_%H:%M:%S")
    print(formatNow + ".csv'\n")
    data = data.split("?")
    with open(f'IMU_DATA/{formatNow}.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter=',')
        for i in range(len(data)-1):
            splitLine = data[i].split(',')
            writer.writerow(splitLine)