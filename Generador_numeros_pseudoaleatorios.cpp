#include "Generador_numeros_pseudoaleatorios.h"
#include <string>
#include <iostream>

Generador_numeros_pseudoaleatorios::Generador_numeros_pseudoaleatorios(int semilla,
                                                                       int cifras)
    : Entrada(semilla, cifras) {}

std::vector<Registro> Generador_numeros_pseudoaleatorios::procedimiento_cuadrado_medio() {
    tabla.clear();

    int rn = semilla;
    int iteraciones = 0;

    while (rn != 0) {
        long long rn2 = 1LL * rn * rn;
        std::string s = std::to_string(rn2);
        if ((s.length() % 2 == 0 && cifras % 2 != 0) ||
            (s.length() % 2 != 0 && cifras % 2 == 0)) {
            s = "0" + s;
        }

        // sacar el centro hasta que quede con 'cifras' dígitos
        std::string centro = s;
        while (centro.length() > static_cast<size_t>(cifras)) {
            centro = centro.substr(1, centro.length() - 2);
        }

        int centro_int = std::stoi(centro);

        Registro reg;
        reg.n    = iteraciones;
        reg.Rn   = rn;
        reg.Rn2  = rn2;
        reg.medio = centro_int;

        tabla.push_back(reg);

        rn = centro_int;
        iteraciones++;
    }

    return tabla;
}

std::vector<int> Generador_numeros_pseudoaleatorios::numeros_pseudoaleatorios() {
    procedimiento_cuadrado_medio();
    std::vector<int> salida;
    salida.reserve(tabla.size());

    for (const auto& r : tabla) {
        salida.push_back(r.medio);
    }

    return salida;
}

void Generador_numeros_pseudoaleatorios::imprimirTabla() const {
    std::cout << "n\tR(n)\tR(n)^2\tM.R(n)^2\n";
    for (const auto& r : tabla) {
        std::cout << r.n << "\t" << r.Rn << "\t" << r.Rn2
                  << "\t" << r.medio << "\n";
    }
}

const std::vector<Registro>& Generador_numeros_pseudoaleatorios::getTabla() const {
    return tabla;
}
