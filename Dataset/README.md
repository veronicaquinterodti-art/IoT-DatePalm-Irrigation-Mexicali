# Dataset

Esta carpeta contiene el conjunto de datos utilizado para evaluar el desempeño de la arquitectura IoT propuesta para el monitoreo de humedad del suelo en el cultivo de palma datilera.

## Archivo

- `Plantacion_datiles_v4.xlsx`

## Variables

| Variable | Descripción |
|----------|-------------|
| Fecha | Fecha de adquisición de la medición |
| Hora | Hora del registro |
| Día | Día de la semana |
| Mes | Mes de adquisición |
| Temperatura (°C) | Temperatura ambiente |
| Watermark Comercial | Lectura del sensor comercial (centibares) |
| Watermark Uni | Lectura obtenida por el sistema IoT desarrollado |
| Riego | Estado del sistema de riego (0 = apagado, 1 = encendido) |
| Error | Diferencia entre ambos sensores |
| Error cuadrático | Valor utilizado para el cálculo del RMSE |

## Descripción

El conjunto de datos fue adquirido durante la evaluación experimental realizada en una plantación de palma datilera ubicada en el Valle de Mexicali, Baja California.

Las mediciones fueron registradas de manera periódica utilizando un sensor comercial Watermark 200SS y el sistema IoT desarrollado en esta investigación.

Estos datos fueron utilizados para calcular las métricas de desempeño, entre ellas el Error Cuadrático Medio (RMSE), el error relativo y el análisis comparativo entre ambos sistemas de medición.
