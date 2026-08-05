# Calibracion

Esta carpeta contiene el procedimiento de calibración utilizado para convertir la resistencia eléctrica medida por el sensor Watermark 200SS en valores de tensión matricial del suelo (centibares), de acuerdo con la metodología empleada en esta investigación.

## Contenido

- `calibracion_watermark.py`
  Script en Python utilizado para analizar la tabla oficial del fabricante Watermark 200SS y generar el procedimiento de calibración empleado por el sistema IoT.

## Descripción

El script realiza las siguientes tareas:

- carga la tabla oficial del sensor Watermark 200SS;
- analiza la relación entre resistencia eléctrica y potencial matricial;
- identifica los puntos de transición entre intervalos;
- genera la información utilizada posteriormente por el firmware del nodo sensor ESP32.


## Referencia

La calibración utilizada corresponde al procedimiento descrito en el Anexo E1 de la tesis.
