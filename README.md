# Práctica 2 — Multiplicación rápida de enteros: Karatsuba

Análisis y Diseño de Algoritmos. Implementación en C++17 de la multiplicación
clásica Θ(n²) y de Karatsuba Θ(n^log₂3), con validación y medición de tiempos.

**Integrantes:** Nicolas Ortiz Alvarez, Samuel Serna

## Requisitos

`g++` con C++17 y `make`. Para la gráfica, `python3` con `matplotlib`.

## Compilar y ejecutar

```sh
make            # Compila todo en build/
make test       # Compara Karatsuba contra el método clásico
make bench      # Mide tiempos, escribe resultados/tiempos.csv y busca el cruce
python3 scripts/graficar.py   # Genera resultados/grafica_tiempos.png
```

## Estructura

| Ruta | Contenido |
|---|---|
| `include/numero.h` | Representación e interfaz pública |
| `src/numero.cpp` | `sumar`, `restar`, `desplazar`, `partir` y conversiones |
| `src/multiplicacion.cpp` | `multiplicacionClasica` y `karatsuba` |
| `tests/validacion.cpp` | Casos del enunciado, de borde y aleatorios |
| `bench/benchmark.cpp` | Medición de tiempos con `steady_clock` |
| `scripts/graficar.py` | Gráfica de tiempo frente a tamaño |
| `resultados/` | Tabla de tiempos y gráfica |

## Decisiones de representación

- `Numero` es un `std::vector<int>` con un dígito por posición en orden
  little-endian: la posición `i` guarda el coeficiente de 10^i.
- Forma normalizada: sin ceros a la izquierda; el cero es `{0}`.
- `karatsuba(a, b)` rellena ambos operandos una sola vez, a la misma potencia
  de 2. La recursión interna no vuelve a rellenar, porque una suma de m+1 dígitos
  subiría de nuevo a 2m y el subproblema no se reduciría a la mitad.
- El caso base de la recursión son los números de 1 dígito.
