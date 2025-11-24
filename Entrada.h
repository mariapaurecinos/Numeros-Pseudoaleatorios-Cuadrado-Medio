#ifndef ENTRADA_H
#define ENTRADA_H

#include <string>

class Entrada {
protected:
    int semilla;
    int cifras;

public:
    Entrada(int semilla, int cifras);

    void entrada_aleatoria();          
    std::string descripcion() const;   

    int getSemilla() const;
    int getCifras() const;
};

#endif // ENTRADA_H
