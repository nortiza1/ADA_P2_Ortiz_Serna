#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "numero.h"

using namespace std::chrono;

typedef vector<pair<Numero, Numero>> Pares;

const int PARES = 5;
const int LOTES = 7;
const int N_MAX = 4096;
const double TIEMPO_MIN_NS = 50000000.0;

volatile unsigned long long sumidero = 0;

Numero aleatorioDeNDigitos(mt19937_64& gen, int n) {
    uniform_int_distribution<int> digito(0, 9);
    uniform_int_distribution<int> primero(1, 9);
    Numero a(n);
    for (int i = 0; i < n; i++) {
        a[i] = digito(gen);
    }
    a[n - 1] = primero(gen);
    return a;
}

Pares generarPares(int n) {
    mt19937_64 gen(1000003ULL * n + 7);
    Pares pares;
    for (int i = 0; i < PARES; i++) {
        Numero a = aleatorioDeNDigitos(gen, n);
        Numero b = aleatorioDeNDigitos(gen, n);
        pares.push_back(make_pair(a, b));
    }
    return pares;
}

double medirRondas(bool usarKaratsuba, const Pares& pares, long long rondas) {
    steady_clock::time_point inicio = steady_clock::now();
    for (long long i = 0; i < rondas; i++) {
        for (int j = 0; j < PARES; j++) {
            Numero r;
            if (usarKaratsuba) {
                r = karatsuba(pares[j].first, pares[j].second);
            } else {
                r = multiplicacionClasica(pares[j].first, pares[j].second);
            }
            sumidero = sumidero + r.size() + r[0];
        }
    }
    steady_clock::time_point fin = steady_clock::now();
    return duration<double, nano>(fin - inicio).count();
}

double medir(bool usarKaratsuba, const Pares& pares) {
    long long rondas = 1;
    while (medirRondas(usarKaratsuba, pares, rondas) < TIEMPO_MIN_NS) {
        rondas = rondas * 2;
    }

    double total = 0;
    for (int i = 0; i < LOTES; i++) {
        total += medirRondas(usarKaratsuba, pares, rondas);
    }
    return total / (LOTES * rondas * PARES);
}

int main() {
    ofstream tiempos("resultados/tiempos.csv");
    tiempos << fixed << setprecision(1);
    tiempos << "n,clasica_ns,karatsuba_ns" << endl;
    cout << fixed << setprecision(1);

    int ultimaDerrota = 0;
    for (int n = 2; n <= N_MAX; n = n * 2) {
        Pares pares = generarPares(n);
        double clasica = medir(false, pares);
        double kara = medir(true, pares);

        if (kara >= clasica) {
            ultimaDerrota = n;
        }

        tiempos << n << "," << clasica << "," << kara << endl;
        cout << "n=" << n << "  clasica=" << clasica << "  karatsuba=" << kara << endl;
    }

    if (ultimaDerrota == N_MAX) {
        cout << "No hay punto de cruce hasta " << N_MAX << " digitos" << endl;
    } else {
        cout << "Karatsuba supera al clasico desde n=" << ultimaDerrota * 2 << endl;
    }
    return 0;
}
