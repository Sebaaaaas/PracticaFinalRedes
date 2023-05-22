#pragma once

#include <vector>

class Barco;

class Tablero {
    
public:
    Tablero();
    ~Tablero();

    //pasamos un barco para colocarlo en el tablero, devuelve falso si no se puede
    bool colocaBarco(Barco* b);

private:
    int filas = 10, columnas = 10;
    std::vector<std::vector<bool>> casillas;

    int barcosRestantes;
};