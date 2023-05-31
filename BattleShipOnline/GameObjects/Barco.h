#pragma once

#include "../Vector2D.h"
#include "../Texture.h"
#include "../Tablero.h"
#include "../Game.h"
#include "../Network/ClientServer.h"
#include "BattleShipObject.h"

#include <SDL2/SDL.h>

enum boat_place {
	RED = 0,
	GREEN = 1
};
class Click;
class Game;

class Barco : public BattleShipObject{
public:

    Barco(Vector2D* p, int w, int h, int longitud_, Texture* t, Tablero* tab, Game* game);
    inline int getX(){return pos->getX();};
    inline int getY(){return pos->getY();};
    inline int getLongitud(){return longitud;};
    inline bool getHorizontal(){return horizontal;};

    void update();
    void render();
    void handleEvent(messageInfo& info);
	void handleEvents(SDL_Event& event){};
    
    //SDL_Rect getRect() const;
    void hayHueco();
    void colocaBarco();
    void rotaBarco();

private:
    int16_t longitud = 0;
    bool horizontal = true;
    boat_place current_boat_place;

    // Texture* tex = nullptr;
    // Vector2D pos;
    Click *boatClick = nullptr;
    Click *clickDeserialize = nullptr;
    // double width; // ancho
	// double height; // alto
    Tablero* currentTablero = nullptr;
    bool colocado = false;
    bool puedeColocarse = true;

    Game* m_game = nullptr;
};

