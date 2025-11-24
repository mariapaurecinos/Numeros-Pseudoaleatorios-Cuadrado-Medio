#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "Entrada.h"
#include "Generador_numeros_pseudoaleatorios.h"
#include <vector>
#include <string>

class Interfaz {
public:
    // Pide semilla y cifras por consola y devuelve un objeto Entrada
    static Entrada pedir_semilla_cifras();

    // Imprime los números pseudoaleatorios (lista de enteros)
    static void imprimir_numeros_pseudoaleatorios(const std::vector<int>& lista);

    // Crea archivo CSV a partir de la tabla (equivalente al DataFrame)
    static void crear_archivo_csv(const std::vector<Registro>& tabla,
                                  const std::string& nombre = "cuadrado_medio.csv");
};

#endif // INTERFAZ_H
