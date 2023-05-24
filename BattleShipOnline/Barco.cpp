#include "Barco.h"
#include <iostream>
#include "ClickSerializer.h"

Barco::Barco(Vector2D p, int w, int h, Texture *t, Tablero* tab) : pos(p), width(w), height(h), tex(t), currentTablero(tab)
{
    //SDL_ShowCursor(SDL_DISABLE);
    boatClick = new Click("CLICK", 0, 0);
    clickDeserialize = new Click("CLICK", 0, 0);
}

void Barco::update()
{
    if(!colocado){
        //std::cout << "hola";
        int x, y;
        SDL_GetMouseState(&x, &y);
        pos = Vector2D(x,y);

        hayHueco();
    }
}

void Barco::render()
{
    tex->renderFrame(getRect(),0, current_boat_place);
}

void Barco::handleEvent()
{
    std::cout << "hola\n";
	// creo un evento auxiliar
	
    int x, y;
    SDL_GetMouseState(&x, &y);
    boatClick->setClickPos(x, y);
    boatClick->toFileAndBack(clickDeserialize);
    if(puedeColocarse && !colocado) {
        colocaBarco();
    }
	
}

SDL_Rect Barco::getRect() const
{
    SDL_Rect rect;
	rect.x = pos.getX(); rect.y = pos.getY();
	rect.w = width, rect.h = height;

	return rect;
}

void Barco::hayHueco(){

    puedeColocarse = true;
    int columnaActual = (pos.getX()- 100)/PIXELES_COLUMNA;
    int filaActual = (pos.getY() - 90)/PIXELES_FILA;
    //comprobamos que no se sale por los lados del tablero(x >> columnas, y >> filas)
    if((pos.getX()-100) < 0 || (columnaActual>= currentTablero->getColumnas()) || (pos.getY() - 90) < 0 || (filaActual >= currentTablero->getFilas())
        || (horizontal && ((columnaActual + (longitud-1)) >= currentTablero->getColumnas()))
        || (!horizontal && ((filaActual+ (longitud -1)) >= currentTablero->getFilas())))
        {
            puedeColocarse = false;
            //std::cout << "pos\n"; 
        }
        

    //comprobamos que no choca con otro barco
    
    else if(horizontal){
        int i = columnaActual;
        int longCheck = i + longitud;
        while(puedeColocarse && (i < longCheck)){
            // std::cout << "check e i y filaActual\n";
            // std::cout << longCheck << "\n";
            // std::cout << i << "\n";
            // std::cout << filaActual << "\n";
            if(currentTablero->getCasillas()[filaActual][i] == true){
                //choca con otro barco
                puedeColocarse = false;
                
                //std::cout << t->getFilas() << "\n";
            } 
            ++i;
        }
    }
    else if(!horizontal){
        int i = filaActual;
        int longCheck = i + longitud;
        while(puedeColocarse && (i < longCheck)){
            if(currentTablero->getCasillas()[i][columnaActual] == true){
                //choca con otro barco
                puedeColocarse = false;
                //std::cout << "vertical\n";
            } 
            ++i;
        }
    }
    if(puedeColocarse){
        //std::cout << "green\n";
        current_boat_place = GREEN;
    }
    else{
        //std::cout << "red\n";
        current_boat_place = RED;
    }

    // std::cout << "pos" << "\n";
    // std::cout << columnaActual << "\n";
    // std::cout << filaActual << "\n";
    //         std::cout << pos.getX()- 100 << "\n";
    //         std::cout << pos.getY() - 90 << "\n";
    //         std::cout << currentTablero->getColumnas() << "\n";
    //         std::cout << currentTablero->getFilas() << "\n";
    //         std::cout << columnaActual + longitud << "\n";
    //         std::cout << filaActual+ longitud << "\n";
}

void Barco::colocaBarco()
{
    int columnaActual = (pos.getX()- 100)/PIXELES_COLUMNA;
    int filaActual = (pos.getY() - 90)/PIXELES_FILA;
    int newPosX = (columnaActual*PIXELES_COLUMNA)+110;
    int newPosY = (filaActual*PIXELES_FILA)+100;
    pos = Vector2D(newPosX, newPosY);
    if(horizontal){
        int i = columnaActual;
        int longCheck = i + longitud;
        while(i < longCheck){
            std::cout << "Antes" << "\n";
            std::cout << true << "\n";
            currentTablero->getCasillas()[filaActual][i] = true;
            std::cout << "despues" << "\n";
            std::cout << currentTablero->getCasillas()[filaActual][i] << "\n";
            ++i;
        }
    }
    else if(!horizontal){
        int i = filaActual;
        int longCheck = i + longitud;
        while(i < longCheck){
            currentTablero->getCasillas()[i][columnaActual] = true;
            std::cout << currentTablero->getCasillas()[i][columnaActual] << "\n";
            ++i;
        }
    }
    colocado = true;
}