#include "numero.h"

Numero multiplicacionClasica(const Numero& a, const Numero& b) {
    int tamA = a.size();
    int tamB = b.size();
    Numero r(tamA + tamB, 0);

    for (int i = 0; i < tamA; i++) {
        int acarreo = 0;
        for (int j = 0; j < tamB; j++) {
            int actual = r[i + j] + a[i] * b[j] + acarreo;
            r[i + j] = actual % 10;
            acarreo = actual / 10;
        }
        r[i + tamB] += acarreo;
    }

    normalizar(r);
    return r;
}

Numero karatsubaRecursivo(const Numero& x, const Numero& y) {
    int n = x.size();
    if ((int)y.size() > n) {
        n = y.size();
    }

    if (n == 1) {
        return multiplicacionClasica(x, y);
    }
    if (esCero(x) || esCero(y)) {
        return Numero(1, 0);
    }

    int m = (n + 1) / 2;

    pair<Numero, Numero> partesX = partir(x, m);
    pair<Numero, Numero> partesY = partir(y, m);
    const Numero& x1 = partesX.first;
    const Numero& x0 = partesX.second;
    const Numero& y1 = partesY.first;
    const Numero& y0 = partesY.second;

    Numero p1 = karatsubaRecursivo(x1, y1);
    Numero p2 = karatsubaRecursivo(x0, y0);
    Numero p3 = karatsubaRecursivo(sumar(x1, x0), sumar(y1, y0));

    Numero central = restar(restar(p3, p1), p2);

    Numero parteAlta = desplazar(p1, 2 * m);
    Numero parteMedia = desplazar(central, m);
    Numero resultado = sumar(sumar(parteAlta, parteMedia), p2);
    return resultado;
}

Numero karatsuba(const Numero& a, const Numero& b) {
    int mayor = a.size();
    if ((int)b.size() > mayor) {
        mayor = b.size();
    }

    int n = potenciaDe2(mayor);
    Numero x = rellenarConCeros(a, n);
    Numero y = rellenarConCeros(b, n);

    return karatsubaRecursivo(x, y);
}
