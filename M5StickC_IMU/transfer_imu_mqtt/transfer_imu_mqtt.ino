// Source code to MQTT connection: https://github.com/m5stack/M5StickC/blob/master/examples/Advanced/MQTT/MQTT.ino

#include <PubSubClient.h>
#include <WiFi.h>

#include "M5StickC.h"
#include <string>

WiFiClient espClient;
PubSubClient client(espClient);

// ------- Variáveis que podem ser alteradas -------
// Configurar a rede WiFi
const char* ssid        = "nome_da_rede_wifi";
const char* password    = "senha_rede_wifi";

const char* mqtt_server = "mqtt.m5stack.com";
const char* topic = "IMUTRANSFER";

// Tempo de coleta de dados (milisegundos)
unsigned long COLLECT_TIME = 60000;
// -------------------------------------------------

unsigned long lastMsg = 0;
String msg;
long value = 0;

float accX = 0.0f;
float accY = 0.0f;
float accZ = 0.0f;

float gyroX = 0.0f;
float gyroY = 0.0f;
float gyroZ = 0.0f;

float pitch = 0.0f;
float roll  = 0.0f;
float yaw   = 0.0f;

int timeCollect = 60;
unsigned long startTime;
bool collect = false;

float data[9];

void getImuData() {
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    M5.IMU.getAhrsData(&pitch, &roll, &yaw);

    data[0] = accX; data[1] = accY; data[2] = accZ;
    data[3] = gyroX; data[4] = gyroY; data[5] = gyroZ;
    data[6] = pitch; data[7] = roll; data[8] = yaw;

    String data_line = "";
    for(int i=0; i<9; i++) {
        String s_data = String(data[i]);
        String aux = (i == 8 ? "?" : ",");
        data_line += s_data + aux;
    }

    msg = data_line;
}

void setupWifi() {
    delay(10);
    M5.Lcd.printf("Connecting to %s", ssid);
    WiFi.mode(WIFI_STA);  // Set the mode to WiFi station mode.
    WiFi.begin(ssid, password);  // Start Wifi connection.

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.print(".");
    }
    M5.Lcd.printf("\nSuccess\n");
}

void callback(char* topic, byte* payload, unsigned int length) {
    M5.Lcd.print("Message arrived [");
    M5.Lcd.print(topic);
    M5.Lcd.println("]");
    if(length == 1) {
      Serial.println("Enviando dados!");
      collect = true;
      startTime = millis() - 5;
      value = 0;
    }
}

void reConnect() {
    while (!client.connected()) {
        M5.Lcd.print("Attempting MQTT connection...");
        
        // Create a random client ID.
        String clientId = "M5Stack-";
        clientId += String(random(0xffff), HEX);
        
        // Attempt to connect.
        if (client.connect(clientId.c_str())) {
            M5.Lcd.printf("\n\nConectado\nExecute o cliente no seu PC para iniciar o envio de dados");
            // Once connected, publish an announcement to the topic.
            // client.publish(topic, "hello world");
            // ... and resubscribe.
            client.subscribe(topic);
        } else {
            M5.Lcd.print("failed, rc=");
            M5.Lcd.print(client.state());
            M5.Lcd.println("try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    M5.begin();
    M5.Lcd.setRotation(3);
    setupWifi();

    client.setServer(mqtt_server, 1883);  // Sets the server details
    client.setCallback(callback);  // Sets the message callback function

    M5.IMU.Init();
    Serial.begin(9600);
}

void loop() {
    if (!client.connected()) {
        reConnect();
    }

    client.loop();  // This function is called periodically to allow clients to
                    // process incoming messages and maintain connections to the
                    // server

    if(!collect) {
      client.subscribe(topic);

    } else {

      unsigned long now = millis();  // Obtain the host startup duration
      if(now - startTime > COLLECT_TIME) {
        collect = false;
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.println("Tempo de coleta esgotado");
        M5.Lcd.println("\nExecute o cliente no seu PC para iniciar o envio de dados");
      }

      // Wait 1s
      if (now - lastMsg > 1000) {
          if (value % 4 == 0) {
              M5.Lcd.fillScreen(BLACK);
              M5.Lcd.setCursor(0, 0);
          }

          ++value;
          lastMsg = now;
          getImuData();
          Serial.println(msg);

          int BUFFER_MSG_SIZE = msg.length() + 1;
          char charMsg[BUFFER_MSG_SIZE];
          for(int i=0; i<BUFFER_MSG_SIZE; i++) charMsg[i] = msg[i];
          Serial.println(charMsg);        
          client.publish(topic, charMsg);  // Publishes a message to the specified topic.
          // client.publish(topic, "Hello");
      }
    }
}