#include "Interfaz.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Entrada Interfaz::pedir_semilla_cifras() {
    int semilla;
    int cifras;

    std::cout << "Ingresar semilla: ";
    std::cin >> semilla;

    std::cout << "Ingresar numero de cifras: ";
    std::cin >> cifras;

    // Crea y devuelve un Entrada (lanza excepción si cifras <= 0)
    return Entrada(semilla, cifras);
}

void Interfaz::imprimir_numeros_pseudoaleatorios(const std::vector<int>& lista) {
    std::cout << "\n=== Numeros pseudoaleatorios ===\n";
    int i = 1;
    for (int num : lista) {
        std::cout << i << ": " << num << "\n";
        ++i;
    }
}

void Interfaz::crear_archivo_csv(const std::vector<Registro>& tabla,
                                 const std::string& nombre) {
    std::ofstream file(nombre);
    if (!file.is_open()) {
        std::cerr << "No se pudo crear el archivo " << nombre << "\n";
        return;
    }

    // Encabezados tipo DataFrame:
    // n, R(n), R(n)^2, M.R(n)^2, u (normalizado a [0,1) usando cifras)
    file << "n,R(n),R(n)^2,M.R(n)^2,u\n";

    if (tabla.empty()) {
        std::cout << "Advertencia: tabla vacia, no hay datos para escribir.\n";
        file.close();
        return;
    }

    // Suponemos que todas las filas comparten el mismo número de cifras,
    // así que usamos el primer valor para deducir el número de cifras:
    int cifras = 0;
    int aux = tabla.front().medio;
    if (aux == 0) {
        cifras = 1;
    } else {
        while (aux > 0) {
            aux /= 10;
            cifras++;
        }
    }

    int modulus = 1;
    for (int i = 0; i < cifras; ++i) modulus *= 10;

    for (const auto& r : tabla) {
        double u = static_cast<double>(r.medio) / static_cast<double>(modulus);
        file << r.n << ","
             << r.Rn << ","
             << r.Rn2 << ","
             << r.medio << ","
             << std::fixed << std::setprecision(6) << u << "\n";
    }

    file.close();
    std::cout << "\nArchivo " << nombre << " creado\n";
}
