#include <iostream>
#include <random>
#include <string>

#include "numero.h"

int aprobadas = 0;
int fallidas = 0;

void comprobar(bool condicion, string nombre) {
    if (condicion) {
        aprobadas++;
    } else {
        fallidas++;
        cout << "  FALLA: " << nombre << endl;
    }
}

void comprobarIgual(string obtenido, string esperado, string nombre) {
    comprobar(obtenido == esperado, nombre + " (obtenido " + obtenido + ", esperado " + esperado + ")");
}

void compararAlgoritmos(string a, string b, string nombre) {
    Numero x = desdeCadena(a);
    Numero y = desdeCadena(b);
    string clasica = aCadena(multiplicacionClasica(x, y));

    comprobarIgual(aCadena(karatsuba(x, y)), clasica, nombre);
    comprobarIgual(aCadena(karatsuba(y, x)), clasica, nombre + " conmutado");
}

void compararConProducto(string a, string b, string esperado, string nombre) {
    Numero x = desdeCadena(a);
    Numero y = desdeCadena(b);
    comprobarIgual(aCadena(multiplicacionClasica(x, y)), esperado, nombre + " clasica");
    comprobarIgual(aCadena(karatsuba(x, y)), esperado, nombre + " karatsuba");
}

string aleatorio(mt19937_64& gen, int digitos) {
    uniform_int_distribution<int> dist(0, 9);
    string s = "";
    for (int i = 0; i < digitos; i++) {
        s += (char)('0' + dist(gen));
    }
    return s;
}

void probarAuxiliares() {
    cout << "Operaciones auxiliares" << endl;

    comprobarIgual(aCadena(desdeCadena("000")), "0", "normaliza el cero");
    comprobarIgual(aCadena(desdeCadena("000123")), "123", "normaliza ceros a la izquierda");
    comprobarIgual(aCadena(sumar(desdeCadena("999"), desdeCadena("1"))), "1000", "suma con acarreo");
    comprobarIgual(aCadena(sumar(desdeCadena("5"), desdeCadena("123456"))), "123461", "suma longitudes distintas");
    comprobarIgual(aCadena(sumar(desdeCadena("0"), desdeCadena("0"))), "0", "suma de ceros");
    comprobarIgual(aCadena(restar(desdeCadena("1000"), desdeCadena("1"))), "999", "resta con prestamos");
    comprobarIgual(aCadena(restar(desdeCadena("1234"), desdeCadena("1234"))), "0", "resta a cero");
    comprobarIgual(aCadena(restar(desdeCadena("500"), desdeCadena("0"))), "500", "resta de cero");
    comprobarIgual(aCadena(desplazar(desdeCadena("123"), 3)), "123000", "desplazar");
    comprobarIgual(aCadena(desplazar(desdeCadena("0"), 5)), "0", "desplazar cero");
    comprobarIgual(aCadena(desplazar(desdeCadena("7"), 0)), "7", "desplazar 0 posiciones");

    pair<Numero, Numero> partes = partir(desdeCadena("12345678"), 4);
    comprobarIgual(aCadena(partes.first), "1234", "partir alta");
    comprobarIgual(aCadena(partes.second), "5678", "partir baja");
    partes = partir(desdeCadena("120005"), 3);
    comprobarIgual(aCadena(partes.first), "120", "partir con ceros alta");
    comprobarIgual(aCadena(partes.second), "5", "partir con ceros baja");
    partes = partir(desdeCadena("42"), 5);
    comprobarIgual(aCadena(partes.first), "0", "partir m grande alta");
    comprobarIgual(aCadena(partes.second), "42", "partir m grande baja");

    comprobar(potenciaDe2(1) == 1, "potencia de 2 de 1");
    comprobar(potenciaDe2(5) == 8, "potencia de 2 de 5");
    comprobar(potenciaDe2(8) == 8, "potencia de 2 de 8");
}

void probarCasosDelEnunciado() {
    cout << "Casos minimos del enunciado" << endl;

    for (int a = 0; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            compararConProducto(to_string(a), to_string(b), to_string(a * b), "1 digito");
        }
    }

    compararConProducto("000000000000123", "0000456", "56088", "ceros izq");
    compararConProducto(string(500, '0') + "7", string(300, '0') + "6", "42", "ceros izq largos");
    compararConProducto(string(64, '0'), "98765", "0", "todo ceros");

    compararConProducto("100000001", "100000001", "10000000200000001", "intercalados");
    compararConProducto("10203", "40506", "413282718", "cuenta corta");
    compararAlgoritmos("1000200030004000", "5000600070008000", "intercalados 16");
    compararAlgoritmos("10" + string(200, '0') + "1", "90" + string(150, '0') + "9", "intercalados largos");

    compararConProducto("123", "45678", "5618394", "impares 3x5");
    compararConProducto("1234567", "891", "1099999197", "impares 7x3");
    compararAlgoritmos("1234567890123", "98765432109", "impares 13x11");

    compararConProducto("99", "99", "9801", "nueves 2");
    compararConProducto("9999", "9999", "99980001", "nueves 4");
    int tamanos[13] = {3, 5, 7, 8, 15, 16, 17, 31, 32, 33, 255, 256, 257};
    for (int i = 0; i < 13; i++) {
        int n = tamanos[i];
        string nueves(n, '9');
        string esperado = string(n - 1, '9') + "8" + string(n - 1, '0') + "1";
        compararConProducto(nueves, nueves, esperado, "nueves n=" + to_string(n));
    }

    compararAlgoritmos(string(1000, '9'), "7", "1000x1");

    mt19937_64 gen(20261101);
    string a1 = aleatorio(gen, 512);
    string b1 = aleatorio(gen, 512);
    compararAlgoritmos(a1, b1, "grande 512");
    string a2 = aleatorio(gen, 777);
    string b2 = aleatorio(gen, 300);
    compararAlgoritmos(a2, b2, "grande 777x300");
    string a3 = aleatorio(gen, 4096);
    string b3 = aleatorio(gen, 4096);
    compararAlgoritmos(a3, b3, "grande 4096");
}

void probarAleatorios() {
    cout << "Pares aleatorios" << endl;
    mt19937_64 gen(42);
    uniform_int_distribution<int> longitud(1, 300);
    for (int i = 0; i < 500; i++) {
        int largoA = longitud(gen);
        int largoB = longitud(gen);
        string a = aleatorio(gen, largoA);
        string b = aleatorio(gen, largoB);
        compararAlgoritmos(a, b, "aleatorio " + to_string(i));
    }
}

int main() {
    probarAuxiliares();
    probarCasosDelEnunciado();
    probarAleatorios();
    cout << "Aprobadas: " << aprobadas << "  Fallidas: " << fallidas << endl;
    if (fallidas == 0) {
        return 0;
    }
    return 1;
}
