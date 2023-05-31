#include "Tablero.h"

#include "Texture.h"
#include "GameObjects/Barco.h"

#include <vector>
#include <iostream>

Tablero::Tablero(Vector2D p, int w, int h, Texture* t) : pos(p), width(w), height(h), tex(t)
{
    printf( "tablero creado!\n" );

    //tablero de 10x10
    casillas.assign(filas, std::vector<bool>(columnas, false));
    barcosRestantes = 0;
}

Tablero::~Tablero(){

}



void Tablero::render(){
    tex->render(getRect());
}

SDL_Rect Tablero::getRect() const
{
	SDL_Rect rect;
	rect.x = pos.getX(); rect.y = pos.getY();
	rect.w = width, rect.h = height;

	return rect;
}
