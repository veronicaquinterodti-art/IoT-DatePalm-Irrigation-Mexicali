"""
calibracion_watermark.py

Script utilizado para analizar la tabla de calibración del sensor
Watermark 200SS durante la investigación doctoral:

"Sistema de IoT de riego de precisión para la optimización
del agua en la agroindustria datilera del Valle de Mexicali"

El programa calcula diferencias consecutivas y tasas de cambio
entre los valores de resistencia eléctrica y potencial matricial,
con el propósito de apoyar la identificación de puntos de quiebre
en la curva característica del sensor.

Autora: Verónica Quintero Rosas
Año: 2026
"""

from pathlib import Path
import math
import sys

# ============================================================
# Configuración
CSV_FILE = Path(__file__).with_name("caltable.csv")
# Índices de las columnas dentro del archivo CSV
COL_X_INDEX = 0  # Resistencia eléctrica
COL_Y_INDEX = 1  # Potencial matricial del suelo
DELIMITER = ","
def cargar_datos(csv_file: Path) -> tuple[list[float], list[float]]:
    """
    Carga los valores de resistencia y potencial matricial
    contenidos en el archivo CSV.

    La primera línea del archivo se considera encabezado.
    """
    x_values: list[float] = []
    y_values: list[float] = []

    try:
        with csv_file.open("r", encoding="utf-8-sig") as file:
            header = file.readline()
            print(f"Encabezados del archivo: {header.strip()}")
            for line_number, line in enumerate(file, start=2):
                line = line.strip()
                if not line:
                    continue
                parts = line.split(DELIMITER)

                try:
                    x_value = float(parts[COL_X_INDEX].strip())
                    y_value = float(parts[COL_Y_INDEX].strip())

                    x_values.append(x_value)
                    y_values.append(y_value)
                except ValueError:
                    print(
                        f"Advertencia: la línea {line_number} contiene "
                        "un valor que no pudo convertirse a número."
                    )
                except IndexError:
                    print(
                        f"Advertencia: la línea {line_number} no contiene "
                        "el número esperado de columnas."
                    )
    except FileNotFoundError:
        print(
            f"Error: no se encontró el archivo '{csv_file.name}'.\n"
            "Debe colocarse en la misma carpeta que este script."
        )
        sys.exit(1)

    except OSError as error:
        print(f"Error al leer el archivo: {error}")
        sys.exit(1)

    if len(x_values) < 2:
        print(
            "Error: se requieren al menos dos observaciones "
            "válidas para calcular las diferencias."
        )
        sys.exit(1)
    return x_values, y_values
def calcular_incrementos(
    x_values: list[float],
    y_values: list[float],
) -> tuple[list[float], list[float], list[float]]:
    """
    Calcula las diferencias consecutivas y la tasa de cambio
    Delta_Y / Delta_X.
    """
    delta_x: list[float] = []
    delta_y: list[float] = []
    tasas_cambio: list[float] = []
    for index in range(1, len(x_values)):
        dx = x_values[index] - x_values[index - 1]
        dy = y_values[index] - y_values[index - 1]
        delta_x.append(dx)
        delta_y.append(dy)
        if dx != 0:
            tasas_cambio.append(dy / dx)
        elif dy != 0:
            tasas_cambio.append(float("inf"))
        else:
            tasas_cambio.append(0.0)
    return delta_x, delta_y, tasas_cambio
def mostrar_resultados(
    x_values: list[float],
    y_values: list[float],
    delta_x: list[float],
    delta_y: list[float],
    tasas_cambio: list[float],
) -> None:
    """Muestra los incrementos y las tasas de cambio calculadas."""
    print("\nDatos cargados correctamente:")
    print(f"Primeros valores de X: {x_values[:5]}")
    print(f"Primeros valores de Y: {y_values[:5]}")
    print("-" * 90)
    print("\n--- Resultados de incrementos ---")
    print(
        "Índice | X original | Y original | "
        "Delta X | Delta Y | Tasa de cambio Y/X"
    )
    print(
        f"{0:<6} | "
        f"{x_values[0]:<10.2f} | "
        f"{y_values[0]:<10.2f} | "
        f"{'-':<7} | "
        f"{'-':<7} | "
        f"{'-':<20}"
    )
    for index, (dx, dy, tasa) in enumerate(
        zip(delta_x, delta_y, tasas_cambio),
        start=1,
    ):
        tasa_texto = (
            f"{tasa:.6f}"
            if math.isfinite(tasa)
            else "infinito"
        )
        print(
            f"{index:<6} | "
            f"{x_values[index]:<10.2f} | "
            f"{y_values[index]:<10.2f} | "
            f"{dx:<7.2f} | "
            f"{dy:<7.2f} | "
            f"{tasa_texto:<20}"
        )
def mostrar_resumen(
    delta_x: list[float],
    delta_y: list[float],
    tasas_cambio: list[float],
) -> None:
    """Calcula y presenta los valores promedio."""
    if not delta_x:
        print("\nNo existen suficientes datos para calcular incrementos.")
        return
    promedio_dx = sum(delta_x) / len(delta_x)
    promedio_dy = sum(delta_y) / len(delta_y)

    tasas_validas = [
        tasa
        for tasa in tasas_cambio
        if math.isfinite(tasa) and tasa != 0.0
    ]

    promedio_tasa = (
        sum(tasas_validas) / len(tasas_validas)
        if tasas_validas
        else float("nan")
    )

    print("\n--- Resumen de incrementos ---")
    print(f"Incremento promedio de X: {promedio_dx:.6f}")
    print(f"Incremento promedio de Y: {promedio_dy:.6f}")
    if math.isfinite(promedio_tasa):
        print(
            "Tasa de cambio promedio "
            f"(Delta_Y/Delta_X): {promedio_tasa:.6f}"
        )
    else:
        print("No fue posible calcular una tasa de cambio promedio.")
def main() -> None:
    """Ejecuta el análisis de la tabla de calibración."""
    x_values, y_values = cargar_datos(CSV_FILE)
    delta_x, delta_y, tasas_cambio = calcular_incrementos(
        x_values,
        y_values,
    )

    mostrar_resultados(
        x_values,
        y_values,
        delta_x,
        delta_y,
        tasas_cambio,
    )

    mostrar_resumen(
        delta_x,
        delta_y,
        tasas_cambio,
    )


if __name__ == "__main__":
    main()
