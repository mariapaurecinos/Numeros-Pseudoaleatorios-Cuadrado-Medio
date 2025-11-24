#include <iostream>
#include "Interfaz.h"
#include "Generador_numeros_pseudoaleatorios.h"

int main() {
    try {
        // Se pide semilla y cifras al usuario:
        Entrada entrada_ejemplo = Interfaz::pedir_semilla_cifras();

        // Se aplica el algoritmo con esa semilla y cifras
        Generador_numeros_pseudoaleatorios algoritmo(
            entrada_ejemplo.getSemilla(),
            entrada_ejemplo.getCifras()
        );

        // Se ejecuta el método del cuadrado medio y se obtiene la tabla
        std::vector<Registro> resultado_tabla = algoritmo.procedimiento_cuadrado_medio();

        // Se obtienen los numeros pseudoaleatorios
        std::vector<int> lista_pseudo = algoritmo.numeros_pseudoaleatorios();

        // Imprimir en consola
        Interfaz::imprimir_numeros_pseudoaleatorios(lista_pseudo);

        // Crear archivo CSV con toda la tabla
        Interfaz::crear_archivo_csv(resultado_tabla, "cuadrado_medio.csv");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
