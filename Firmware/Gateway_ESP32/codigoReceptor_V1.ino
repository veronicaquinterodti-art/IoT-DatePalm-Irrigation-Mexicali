/*
-------------------------------------------------------------
 codigoReceptor_V1.ino
 Firmware del gateway ESP32 desarrollado para la investigación:
 "Internet de las Cosas (IoT) en la optimización del agua
 en la agroindustria datilera:
 Caso de estudio Valle de Mexicali, Baja California"
 Funciones principales:
 - Recibir datos provenientes del nodo sensor mediante XBee.
 - Conectarse a una red Wi-Fi.
 - Establecer una conexión MQTT segura con AWS IoT Core.
 - Publicar las mediciones en formato JSON.
 - Gestionar la reconexión automática.

 Autora:
 Verónica Quintero Rosas

 Año:
 2026
-------------------------------------------------------------
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "misCredenciales_template.h"

WiFiClientSecure net;
PubSubClient client(net);
String incomingData;
//==========================
// Prototipos de funciones


void WiFi_setup();
void setClient_AWS();
void reconnect();
void callback(char* topic, byte* payload, unsigned int length);
void publish_mqtt(String mensaje);
void receive_data();

//==========================
// Configuración inicial

void setup() {
  Serial.begin(9600);
  WiFi_setup();
  setClient_AWS();
}

//==========================
//  principal
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  receive_data();
}
//==========================
// Conexión a la red Wi-Fi
//==========================
void WiFi_setup() {
  Serial.print("Intentando conectar a la red Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Conexión Wi-Fi establecida.");
}
//==========================
// Configuración del cliente AWS IoT Core
//==========================
void setClient_AWS() {
  net.setCACert(AWS_ROOT_CA);
  net.setCertificate(DEVICE_CERTIFICATE);
  net.setPrivateKey(DEVICE_PRIVATE_KEY);
  client.setServer(server, 8883);
  client.setCallback(callback);
  delay(100);
}
//==========================
// Recepción de mensajes MQTT
//==========================

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en el tópico: ");
  Serial.println(topic);
  Serial.print("Contenido: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

//==========================
// Reconexión MQTT
//==========================

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando a AWS IoT Core... ");
    if (client.connect(THINGNAME)) {
      Serial.println("Conectado.");
    } else {
      Serial.print("Error. Código = ");
      Serial.println(client.state());
      delay(5000);
    }

  }

}
//==========================
// Publicación de datos en MQTT
//==========================

void publish_mqtt(String mensaje) {
  if (mensaje.length() == 0) {
    return;
  }

  if (!client.connected()) {
    reconnect();
  }
  Serial.print("Publicando mensaje JSON: ");
  Serial.println(mensaje);
  const bool publicado = client.publish(
    MQTT_TOPIC,
    mensaje.c_str()
  );

  if (publicado) {
    Serial.println("Mensaje publicado correctamente.");
  } else {
    Serial.println("Error al publicar el mensaje.");
  }
}

//==========================
// Recepción de datos desde XBee
//==========================

void receive_data() {
  if (Serial.available() > 0) {
    incomingData = Serial.readStringUntil('\n');
    incomingData.trim();
    if (incomingData.length() > 0) {
      publish_mqtt(incomingData);
    }
  }
}
