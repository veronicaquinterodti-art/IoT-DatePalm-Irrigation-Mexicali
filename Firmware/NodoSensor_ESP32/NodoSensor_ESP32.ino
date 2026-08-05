/*
  NodoSensor_ESP32.ino

  Firmware del nodo sensor utilizado en la investigación:
  "Sistema IoT para la optimización del agua en la agroindustria datilera".

  Funciones principales:
  - Lectura del sensor Watermark 200SS.
  - Cálculo de la resistencia eléctrica.
  - Conversión a tensión matricial del suelo (centibares).
  - Registro de fecha y hora mediante RTC.
  - Generación de mensajes JSON.
  - Transmisión de datos mediante XBee.
*/

#include <Wire.h>
#include <RTClib.h>
// Pines ADC
const int sensorPin0 = 34;
const int sensorPin1 = 35;
// Alimentación del sensor
const int powerPinA = 33;
const int powerPinB = 32;

// Resistencia de referencia
const float Rref = 8200.0;

// Variables de adquisición
int sensorValue0 = 0;
int sensorValue1 = 0;

float buffer0 = 0;
float buffer1 = 0;

float Rx = 0;
// RTC
RTC_DS1307 rtc;
// Fecha y hora
char fecha_str[11];
char hora_str[9];
char sensor_data[10];
const char sensor_ID[] = "WTMK1";
// Intervalo de muestreo
const unsigned long INTERVALO_ACCION_SEGUNDOS = 3600UL;
unsigned long tiempoUltimaAccion = 0;
// Prototipos
float watermark();
void actualizarFechaHora();
void sendSerial();
void setup() {
  Serial.begin(9600);
  Wire.begin();
  if (!rtc.begin()) {
    Serial.println("Error: no se encontró el módulo RTC DS1307.");
    Serial.flush();
    while (true) {
      delay(1000);
    }
  }

  /*
     sincronizar el RTC
    con la fecha y hora de compilación:
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  */
  pinMode(powerPinA, OUTPUT);
  pinMode(powerPinB, OUTPUT);
  digitalWrite(powerPinA, LOW);
  digitalWrite(powerPinB, LOW);
  // Configuración del ADC del ESP32
  analogSetAttenuation(ADC_11db);
  // realizar una lectura inmediatamente al iniciar
  tiempoUltimaAccion =
      millis() - (INTERVALO_ACCION_SEGUNDOS * 1000UL);
}

void loop() {
  const unsigned long intervaloMs =
      INTERVALO_ACCION_SEGUNDOS * 1000UL;
  if ((millis() - tiempoUltimaAccion) >= intervaloMs) {
    actualizarFechaHora();
    sendSerial();
    tiempoUltimaAccion = millis();
  }

  delay(1000);
}
float watermark() {
  buffer0 = 0.0;
  buffer1 = 0.0;
  digitalWrite(powerPinA, HIGH);
  digitalWrite(powerPinB, LOW);
  delayMicroseconds(80);
  const int muestras = 9;
  for (int i = 0; i < muestras; i++) {
    sensorValue1 = analogRead(sensorPin1);
    sensorValue0 = analogRead(sensorPin0);
    buffer1 += sensorValue1;
    buffer0 += sensorValue0;
  }
  digitalWrite(powerPinA, LOW);
  delayMicroseconds(2450);
  digitalWrite(powerPinB, HIGH);
  delayMicroseconds(2450);
  digitalWrite(powerPinB, LOW);
  if (buffer1 <= 0.0) {
    return 0.0;
  }
  Rx = ((buffer0 / buffer1) - 1.0) * Rref;
  float moisture = 0.0;
  /*
    Curva de calibración segmentada
    Sensor Watermark 200SS
  */
  if (Rx < 550.0) {
    moisture = 0.0;
  }
  else if (Rx < 1000.0) {
    moisture = (0.02 * Rx) - 11.0;
  }
  else if (Rx < 1100.0) {
    moisture = (0.01 * Rx) - 1.0;
  }
  else if (Rx < 1280.0) {
    moisture = (0.00555 * Rx) + 3.895;
  }
  else if (Rx < 2000.0) {
    moisture = (0.00555 * Rx) + 3.896;
  }
  else if (Rx < 6000.0) {
    moisture = (0.005 * Rx) + 5.0;
  }
  else if (Rx < 9200.0) {
    moisture = (0.00625 * Rx) - 2.5;
  }
  else if (Rx < 12200.0) {
    moisture = (0.00666 * Rx) - 6.272;
  }
  else if (Rx < 15575.0) {
    moisture = (0.00740 * Rx) - 15.28;
  }
  else if (Rx < 27575.0) {
    moisture = (0.008 * Rx) - 24.6;
  }
  else if (Rx < 27770.0) {
    moisture = (0.00512 * Rx) + 54.816;
  }
  else if (Rx <= 27950.0) {
    moisture = (0.008 * Rx) - 24.6;
  }
  else {
    moisture = 199.0;
  }

  return moisture;

}
void actualizarFechaHora() {
  const DateTime now = rtc.now();
  snprintf(
    fecha_str,
    sizeof(fecha_str),
    "%02d/%02d/%04d",
    now.day(),
    now.month(),
    now.year()
  );
  snprintf(
    hora_str,
    sizeof(hora_str),
    "%02d:%02d:%02d",
    now.hour(),
    now.minute(),
    now.second()
  );
}

void sendSerial() {
  const float lectura = watermark();
  dtostrf(
    lectura,
    0,
    2,
    sensor_data
  );
  char msg[128];
  const int charsWritten = snprintf(
    msg,
    sizeof(msg),
    "{\"Date\":\"%s\",\"Time\":\"%s\","
    "\"sensor_ID\":\"%s\",\"sensor_Read\":\"%s\"}",
    fecha_str,
    hora_str,
    sensor_ID,
    sensor_data
  );
  if (
    charsWritten > 0 &&
    charsWritten < static_cast<int>(sizeof(msg))
  ) {
    Serial.println(msg);
  } else {
    Serial.println(
      "ERROR: el mensaje JSON fue truncado o no pudo generarse."
    );
  }
}
