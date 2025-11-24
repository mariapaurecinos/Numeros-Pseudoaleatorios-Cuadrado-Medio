#include "Entrada.h"
#include <stdexcept>
#include <random>

Entrada::Entrada(int semilla, int cifras) {
    if (cifras <= 0) {
        throw std::invalid_argument("No es posible seleccionar 0 cifras");
    }
    this->semilla = semilla;
    this->cifras = cifras;
}

void Entrada::entrada_aleatoria() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> semilla_dist(0, 99999);
    std::uniform_int_distribution<> cifras_dist(1, 5);

    semilla = semilla_dist(gen);
    cifras = cifras_dist(gen);
}

std::string Entrada::descripcion() const {
    return "Entrada con " + std::to_string(cifras) +
           " cifras y semilla " + std::to_string(semilla);
}

int Entrada::getSemilla() const {
    return semilla;
}

int Entrada::getCifras() const {
    return cifras;
}
