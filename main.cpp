#include <iostream>
#include <string>

#include "numero.h"

bool soloDigitos(const string& s) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

int main() {
    string a, b;

    cout << "Primer numero: ";
    cin >> a;
    cout << "Segundo numero: ";
    cin >> b;

    if (!soloDigitos(a) || !soloDigitos(b)) {
        cout << "Error: escriba solo digitos" << endl;
        return 1;
    }

    Numero x = desdeCadena(a);
    Numero y = desdeCadena(b);

    cout << "Clasica:   " << aCadena(multiplicacionClasica(x, y)) << endl;
    cout << "Karatsuba: " << aCadena(karatsuba(x, y)) << endl;
    return 0;
}
