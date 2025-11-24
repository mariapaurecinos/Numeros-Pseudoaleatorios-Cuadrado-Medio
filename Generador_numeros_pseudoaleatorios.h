#ifndef GENERADOR_NUMEROS_PSEUDOALEATORIOS_H
#define GENERADOR_NUMEROS_PSEUDOALEATORIOS_H

#include "Entrada.h"
#include <vector>

struct Registro {
    int n;
    long long Rn;
    long long Rn2;
    int medio;
};

class Generador_numeros_pseudoaleatorios : public Entrada {
private:
    std::vector<Registro> tabla;

public:
    Generador_numeros_pseudoaleatorios(int semilla, int cifras);

    // ejecuta el método del cuadrado medio y llena la tabla
    std::vector<Registro> procedimiento_cuadrado_medio();

    // devuelve solo la columna M.R(n)^2 (los "números pseudoaleatorios")
    std::vector<int> numeros_pseudoaleatorios();

    // imprime la tabla en consola
    void imprimirTabla() const;

    // para acceder a la tabla desde main
    const std::vector<Registro>& getTabla() const;
};

#endif // GENERADOR_NUMEROS_PSEUDOALEATORIOS_H
