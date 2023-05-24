#ifndef TABLERO_H_
#define TABLERO_H_

#include <SDL2/SDL.h>
#include "Vector2D.h"
#include <vector>

class Barco;
class Texture;

const int PIXELES_COLUMNA = 46;
const int PIXELES_FILA = 40;

class Tablero {
    
public:
    Tablero(Vector2D pos, int w, int h, Texture* t);
    ~Tablero();
    void render();
    SDL_Rect getRect() const;
    inline int getFilas(){return filas;};
    inline int getColumnas(){return columnas;};
    inline std::vector<std::vector<bool>> &getCasillas(){ return casillas;};


private:
    int filas = 8, columnas = 10;
    std::vector<std::vector<bool>> casillas;

    int barcosRestantes;

    Texture* tex = nullptr;
    Vector2D pos;
    double width; // ancho
	double height; // alto
};
#endif