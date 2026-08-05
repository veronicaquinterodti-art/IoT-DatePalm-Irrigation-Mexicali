# Calibracion

Esta carpeta contiene el procedimiento de calibración utilizado para convertir la resistencia eléctrica medida por el sensor Watermark 200SS en valores de tensión matricial del suelo (centibares), de acuerdo con la metodología empleada en esta investigación.
## Contenido

- `calibracion_watermark.py`  
  Script en Python utilizado para analizar la tabla oficial del fabricante y generar la curva de calibración.

- `caltable.csv`  
  Tabla de calibración utilizada por el firmware del nodo sensor ESP32.

## Descripción

El script realiza las siguientes tareas:

- tabla oficial del sensor Watermark 200SS;
- analiza la relación entre resistencia eléctrica y potencial matricial;
- identifica los puntos de transición entre intervalos;
- genera la tabla de calibración utilizada posteriormente por el firmware del sistema IoT.

## Referencia

La calibración utilizada corresponde al procedimiento descrito en el Anexo E1 de la tesis.
