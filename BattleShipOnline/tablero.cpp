#include "tablero.h"

#include <iostream>

class Barco{

public:
    inline int getX(){return posX;};
    inline int getY(){return posY;};
    inline int getLongitud(){return longitud;};
    inline bool getHorizontal(){return horizontal;};

private:
    int posX, posY;
    int longitud;
    bool horizontal;
};

Tablero::Tablero(){
    printf( "tablero creado!\n" );

    //tablero de 10x10
    casillas.assign(filas, std::vector<bool>(columnas, false));
    barcosRestantes = 0;
}

Tablero::~Tablero(){

}

bool Tablero::colocaBarco(Barco* b){
    
    //comprobamos que no se sale por los lados del tablero(x >> columnas, y >> filas)
    if(b->getX() < 0 || b->getX() > columnas || b->getY() < 0 || b->getY() > filas
        || (b->getHorizontal() && b->getX() + b->getLongitud() > columnas)
        || (!b->getHorizontal() && b->getX() + b->getLongitud() > filas))
        return false;

    //comprobamos que no choca con otro barco
    bool exito = true;
    if(b->getHorizontal()){
        int i = b->getX();
        while(exito && i < b->getLongitud()){
            if(casillas[i][b->getY()] == true) //choca con otro barco
                exito = false;
            ++i;
        }
    }
    else{
        int i = b->getY();
        while(exito && i < b->getLongitud()){
            if(casillas[b->getX()][i] == true) //choca con otro barco
                exito = false;
            ++i;
        }
    }

    return exito;
}
