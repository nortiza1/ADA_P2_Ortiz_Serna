#include "numero.h"

Numero desdeCadena(const string& s) {
    Numero a;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        a.push_back(s[i] - '0');
    }
    normalizar(a);
    return a;
}

string aCadena(const Numero& a) {
    Numero copia = a;
    normalizar(copia);
    string s = "";
    for (int i = (int)copia.size() - 1; i >= 0; i--) {
        s += (char)('0' + copia[i]);
    }
    return s;
}

void normalizar(Numero& a) {
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    if (a.empty()) {
        a.push_back(0);
    }
}

bool esCero(const Numero& a) {
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != 0) {
            return false;
        }
    }
    return true;
}

Numero rellenarConCeros(const Numero& a, int longitud) {
    Numero r = a;
    if ((int)r.size() < longitud) {
        r.resize(longitud, 0);
    }
    return r;
}

int potenciaDe2(int n) {
    int p = 1;
    while (p < n) {
        p = p * 2;
    }
    return p;
}

Numero sumar(const Numero& a, const Numero& b) {
    int tamA = a.size();
    int tamB = b.size();
    int n = tamA;
    if (tamB > n) {
        n = tamB;
    }

    Numero r;
    r.reserve(n + 1);
    int acarreo = 0;
    for (int i = 0; i < n; i++) {
        int digitoA = 0;
        int digitoB = 0;
        if (i < tamA) {
            digitoA = a[i];
        }
        if (i < tamB) {
            digitoB = b[i];
        }
        int suma = digitoA + digitoB + acarreo;
        r.push_back(suma % 10);
        acarreo = suma / 10;
    }
    if (acarreo > 0) {
        r.push_back(acarreo);
    }
    normalizar(r);
    return r;
}

Numero restar(const Numero& a, const Numero& b) {
    Numero r = rellenarConCeros(a, b.size());
    int tamB = b.size();
    int prestamo = 0;
    for (int i = 0; i < (int)r.size(); i++) {
        int digitoB = 0;
        if (i < tamB) {
            digitoB = b[i];
        }
        int resta = r[i] - digitoB - prestamo;
        if (resta < 0) {
            resta = resta + 10;
            prestamo = 1;
        } else {
            prestamo = 0;
        }
        r[i] = resta;
    }
    normalizar(r);
    return r;
}

Numero desplazar(const Numero& a, int k) {
    if (esCero(a)) {
        return Numero(1, 0);
    }
    Numero r(k, 0);
    r.insert(r.end(), a.begin(), a.end());
    normalizar(r);
    return r;
}

pair<Numero, Numero> partir(const Numero& a, int m) {
    int corte = m;
    if (corte > (int)a.size()) {
        corte = a.size();
    }
    pair<Numero, Numero> partes;
    partes.first.assign(a.begin() + corte, a.end());
    partes.second.assign(a.begin(), a.begin() + corte);
    normalizar(partes.first);
    normalizar(partes.second);
    return partes;
}
