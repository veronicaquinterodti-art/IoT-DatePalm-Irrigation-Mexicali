#ifndef MISCREDENCIALES_TEMPLATE_H
#define MISCREDENCIALES_TEMPLATE_H
//----------------------------------------------------
// Configuración Wi-Fi
const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";
//----------------------------------------------------
// AWS IoT Core
const char* server = "xxxxxxxxxxxx-ats.iot.us-east-1.amazonaws.com";
const char* THINGNAME = "ESP32_Gateway";
const char* MQTT_TOPIC = "Watermark_data";
//----------------------------------------------------
// Certificados
//----------------------------------------------------
const char AWS_ROOT_CA[] = R"EOF(
PEGAR_AQUI_EL_CERTIFICADO_RAIZ
)EOF";
const char DEVICE_CERTIFICATE[] = R"EOF(
PEGAR_AQUI_EL_CERTIFICADO_DEL_DISPOSITIVO
)EOF";
const char DEVICE_PRIVATE_KEY[] = R"EOF(
PEGAR_AQUI_LA_LLAVE_PRIVADA
)EOF";
#endif
