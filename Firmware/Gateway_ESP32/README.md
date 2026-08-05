# Gateway_ESP32

Esta carpeta contiene el firmware del gateway ESP32 encargado de la comunicación entre la red local XBee y la plataforma AWS IoT Core.

Sus funciones principales son:

- Recibir las mediciones provenientes del nodo sensor mediante comunicación serial.
- Conectarse a la red Wi-Fi.
- Establecer una conexión segura con AWS IoT Core mediante MQTT sobre TLS.
- Publicar las mediciones en formato JSON.
- Gestionar la reconexión automática con el bróker MQTT.
