import csv

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt

n = []
clasica = []
karatsuba = []
with open("resultados/tiempos.csv") as archivo:
    for fila in csv.DictReader(archivo):
        n.append(int(fila["n"]))
        clasica.append(float(fila["clasica_ns"]) / 1e6)
        karatsuba.append(float(fila["karatsuba_ns"]) / 1e6)

plt.plot(n, clasica, marker="o", color="#2a78d6", label="Clásica")
plt.plot(n, karatsuba, marker="s", color="#eb6834", label="Karatsuba")
plt.xscale("log", base=2)
plt.yscale("log")
plt.xlabel("Dígitos (n)")
plt.ylabel("Tiempo por producto (ms)")
plt.title("Tiempo vs. tamaño")
plt.grid(True, color="#e4e3df")
plt.legend()
plt.savefig("resultados/grafica_tiempos.png", dpi=200)
