#ifndef NUMERO_H
#define NUMERO_H

#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef vector<int> Numero;

Numero desdeCadena(const string& s);
string aCadena(const Numero& a);
void normalizar(Numero& a);
bool esCero(const Numero& a);
Numero rellenarConCeros(const Numero& a, int longitud);
int potenciaDe2(int n);

Numero sumar(const Numero& a, const Numero& b);
Numero restar(const Numero& a, const Numero& b);
Numero desplazar(const Numero& a, int k);
pair<Numero, Numero> partir(const Numero& a, int m);

Numero multiplicacionClasica(const Numero& a, const Numero& b);
Numero karatsuba(const Numero& a, const Numero& b);

#endif
