# Sistema de IoT de riego de precisión para la optimización del agua en la agroindustria datilera del Valle de Mexicali

<p align="center">
<img src="prototipo_principal.jpg" width="250">
</p>

## Repositorio oficial de la investigación 

**Autora:** Verónica Quintero Rosas

**Año:** 2026

---

# Descripción

Este repositorio contiene el firmware, los procedimientos de calibración, el conjunto de datos experimentales, la documentación técnica y los resultados obtenidos durante el desarrollo de la investigación doctoral titulada:

> **Sistema de IoT de riego de precisión para la optimización del agua en la agroindustria datilera del Valle de Mexicali.**

La investigación propone una arquitectura IoT de bajo costo para el monitoreo continuo de la humedad del suelo utilizando sensores Watermark 200SS, comunicación inalámbrica mediante módulos XBee y almacenamiento seguro de datos en la nube mediante Amazon Web Services (AWS).

---

# Objetivo general

Evaluar la eficiencia hídrica y el desempeño de una arquitectura basada en Internet de las Cosas (IoT) para optimizar el riego de precisión en el cultivo de palma datilera bajo condiciones reales de operación en el Valle de Mexicali.

---

# Arquitectura del sistema

El sistema desarrollado está conformado por cinco componentes principales:

- Sensor Watermark 200SS
- ESP32
- Comunicación inalámbrica mediante XBee IEEE 802.15.4
- AWS IoT Core
- Base de datos DynamoDB

La arquitectura permite adquirir datos del suelo, transmitirlos de manera inalámbrica y almacenarlos automáticamente en la nube para su análisis posterior.

---

# Organización del repositorio

```
AWS/
│
├── Certificados
├── AWS IoT Core
├── Lambda
└── DynamoDB

Calibration/
│
├── Curvas de calibración
├── Scripts
└── Procedimientos

Dataset/
│
├── Datos experimentales
├── Variables
└── Diccionario de datos

Documentation/
│
├── Diagramas
├── Manuales
├── Arquitectura
└── Publicaciones

Firmware/
│
├── ESP32 Emisor
├── ESP32 Receptor
├── Librerías
└── Configuración

Results/
│
├── Figuras
├── Tablas
├── Métricas
└── Resultados estadísticos
```

---

# Hardware utilizado

- ESP32
- Sensor Watermark 200SS
- Sensor DHT11
- Módulos XBee
- Fuente de alimentación
- Red Wi-Fi

---

# Software utilizado

- Arduino IDE
- XCTU
- AWS IoT Core
- AWS Lambda
- DynamoDB
- MQTT
- GitHub

---

# Resultados principales

Durante la validación experimental se obtuvieron:

- 2232 mediciones pareadas
- RMSE ≈ 2.30 cb
- NRMSE ≈ 5.8 %
- Reducción aproximada del 60 % en el consumo de agua
- Validación experimental bajo condiciones reales de operación

---

# Contenido del repositorio

| Carpeta | Contenido |
|----------|-----------|
| Firmware | Código fuente del sistema |
| Calibration | Calibración del sensor Watermark |
| Dataset | Base de datos experimental |
| Documentation | Diagramas y documentación técnica |
| Results | Figuras, tablas y resultados |
| AWS | Configuración de servicios en la nube |

---

# Licencia

Este proyecto se distribuye bajo la licencia MIT.

---

# Cita

Si este trabajo resulta útil para tu investigación, por favor cita:

**Quintero Rosas, V. (2026). Sistema de IoT de riego de precisión para la optimización del agua en la agroindustria datilera del Valle de Mexicali.**

---

# Contacto

Verónica Quintero Rosas
README científico completo

México

2026
