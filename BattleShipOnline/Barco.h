#ifndef BARCO_H_
#define BARCO_H_
#include "Vector2D.h"
#include <SDL2/SDL.h>
#include "Texture.h"
#include "Tablero.h"
#include "ClientServer.h"

enum boat_place {
	RED = 0,
	GREEN = 1
};
class Click;

class Barco{
public:

    Barco(Vector2D p, int w, int h, Texture* t, Tablero* tab);
    inline int getX(){return pos.getX();};
    inline int getY(){return pos.getY();};
    inline int getLongitud(){return longitud;};
    inline bool getHorizontal(){return horizontal;};

    void update();
    void render();
    void handleEvent(messageInfo& info);
    
    SDL_Rect getRect() const;
    void hayHueco();
    void colocaBarco();

private:
    int16_t longitud = 2;
    bool horizontal = true;
    boat_place current_boat_place;

    Texture* tex = nullptr;
    Vector2D pos;
    Click *boatClick = nullptr;
    Click *clickDeserialize = nullptr;
    double width; // ancho
	double height; // alto
    Tablero* currentTablero = nullptr;
    bool colocado = false;
    bool puedeColocarse = true;
};
#endif

