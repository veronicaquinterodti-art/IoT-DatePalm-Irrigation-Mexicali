# Configuración de la regla en AWS IoT Core (SQL, AWS Lambda y Amazon DynamoDB)

Esta carpeta contiene la documentación técnica correspondiente a la configuración de la infraestructura en la nube utilizada durante el desarrollo del sistema IoT para el monitoreo de humedad del suelo en la agroindustria datilera.

El contenido presentado corresponde al procedimiento descrito en el **Anexo C** del docuemnto del proyecto.... documenta la integración entre AWS IoT Core, AWS Lambda y Amazon DynamoDB para el procesamiento y almacenamiento automático de las mediciones enviadas por el gateway ESP32.

---

## Objetivo

Documentar el procedimiento necesario para configurar la plataforma AWS utilizada durante la investigación, permitiendo reproducir el flujo de adquisición, procesamiento y almacenamiento de datos implementado en el sistema IoT.

---

## Contenido

Esta carpeta incluye la documentación referente a:

- Creación del dispositivo (Thing) en AWS IoT Core.
- Registro de certificados digitales X.509.
- Configuración de políticas de acceso.
- Configuración del tópico MQTT.
- Creación de la regla de AWS IoT Core.
- Definición de la sentencia SQL utilizada por la regla.
- Configuración de la función AWS Lambda.
- Código implementado en la función Lambda.
- Creación y configuración de la tabla Amazon DynamoDB.
- Configuración de roles y permisos IAM.
- Verificación del almacenamiento automático de los datos.

---

## Flujo de procesamiento

