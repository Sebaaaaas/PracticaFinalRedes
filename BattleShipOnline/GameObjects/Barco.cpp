#include "Barco.h"

#include <iostream>

Barco::Barco(Vector2D* p, int w, int h, int longitud_, Texture* t, Tablero* tab, Game* game) : BattleShipObject(p, w * longitud_, h, t), longitud(longitud_), currentTablero(tab)
{
    //SDL_ShowCursor(SDL_DISABLE);
    boatClick = new Click("CLICK", 0, 0);
    clickDeserialize = new Click("CLICK", 0, 0);
    m_game = game;
}

void Barco::update()
{
    if(!colocado){
        int x, y;
        SDL_GetMouseState(&x, &y);
        pos = new Vector2D(x,y);
        hayHueco();
    }
}

void Barco::render()
{
    if(horizontal)
        tex->renderFrame(getRect(),0, current_boat_place);
    else
        tex->renderFrame(getRect(),0, current_boat_place, 90);
}

void Barco::handleEvents(SDL_Event& event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
        // creo un evento auxiliar
            setupInfo info;
            int x, y;
            SDL_GetMouseState(&x, &y);
            boatClick->setClickPos(x, y);
            boatClick->toFileAndBack(clickDeserialize);

            if(puedeColocarse && !colocado) {
                colocaBarco();
                info.pos = Vector2D(x, y);
                info.horizontal = horizontal;
                info.longitud = longitud;
                info.isMessage = true;
                m_game->setBarcoCogido();
                m_game->createMessage(info);
            }
        }
    }
    else if(!colocado && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){
        rotaBarco();
    }
}

void Barco::hayHueco(){

    puedeColocarse = true;
    int columnaActual = (pos->getX()- OFFSET_X)/PIXELES_COLUMNA;
    int filaActual = (pos->getY() - OFFSET_Y)/PIXELES_FILA;
    //comprobamos que no se sale por los lados del tablero(x >> columnas, y >> filas)
    if((pos->getX()-OFFSET_X) < 0 || (columnaActual>= currentTablero->getColumnas()) || (pos->getY() - OFFSET_Y) < 0 || (filaActual >= currentTablero->getFilas())
        || (horizontal && ((columnaActual + (longitud-1)) >= currentTablero->getColumnas()))
        || (!horizontal && ((filaActual+ (longitud -1)) >= currentTablero->getFilas())))
        {
            puedeColocarse = false;
        }
        

    //comprobamos que no choca con otro barco
    
    else if(horizontal){
        int i = columnaActual;
        int longCheck = i + longitud;
        while(puedeColocarse && (i < longCheck)){
            if(currentTablero->getCasillas()[filaActual][i] == true){
                //choca con otro barco
                puedeColocarse = false;
            } 
            ++i;
        }
    }
    else if(!horizontal){
        int i = filaActual;
        int longCheck = i + longitud;
        while(puedeColocarse && (i < longCheck)){
            if(currentTablero->getCasillas()[i][columnaActual] == true){
                puedeColocarse = false;
            } 
            ++i;
        }
    }
    if(puedeColocarse){
        current_boat_place = GREEN;
    }
    else{
        current_boat_place = RED;
    }

}

void Barco::colocaBarco()
{
    int columnaActual = (pos->getX()- OFFSET_X)/PIXELES_COLUMNA;
    int filaActual = (pos->getY() - OFFSET_Y)/PIXELES_FILA;
    int newPosX = (columnaActual*PIXELES_COLUMNA)+110;
    int newPosY = (filaActual*PIXELES_FILA)+100;
    pos = new Vector2D(newPosX, newPosY);
    if(horizontal){
        int i = columnaActual;
        int longCheck = i + longitud;
        while(i < longCheck){
            currentTablero->getCasillas()[filaActual][i] = true;
            ++i;
        }
    }
    else if(!horizontal){
        int i = filaActual;
        int longCheck = i + longitud;
        while(i < longCheck){
            currentTablero->getCasillas()[i][columnaActual] = true;
            ++i;
        }
    }
    colocado = true;
}

void Barco::rotaBarco(){
    horizontal = !horizontal;
}