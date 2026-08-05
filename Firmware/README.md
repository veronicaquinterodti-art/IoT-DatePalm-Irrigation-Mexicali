# Firmware

Esta carpeta contiene el firmware desarrollado para los dos microcontroladores ESP32 que integran la arquitectura IoT de la investigación.

## Organización

### NodoSensor_ESP32

Firmware encargado de:

- adquirir las señales del sensor Watermark 200SS;
- calcular la resistencia eléctrica del sensor;
- transformar la lectura a tensión matricial del suelo en centibares;
- registrar fecha y hora mediante el módulo RTC;
- construir el mensaje en formato JSON;
- transmitir los datos por UART hacia el módulo XBee transmisor.

### Gateway_ESP32

Firmware encargado de:

- recibir por comunicación serial los datos enviados por el módulo XBee receptor;
- conectarse a una red Wi-Fi;
- establecer una conexión MQTT segura con AWS IoT Core mediante TLS;
- publicar las mediciones en formato JSON;
- gestionar la reconexión automática con el bróker.

## Archivos previstos

```text
Firmware/
├── NodoSensor_ESP32/
│   └── NodoSensor_ESP32.ino
├── Gateway_ESP32/
│   ├── codigoReceptor_V1.ino
│   └── misCredenciales_template.h
└── README.md
