#ifndef TABLERO_H_
#define TABLERO_H_

#include <SDL2/SDL.h>
#include "../Vector2D.h"
#include <vector>
#include "BattleShipObject.h"
#include "../Network/ClientServer.h"

class Barco;
class Texture;
class Game;

const int PIXELES_COLUMNA = 46;
const int PIXELES_FILA = 40;

const int OFFSET_X = 100;
const int OFFSET_Y = 90;

typedef struct{
    bool clicado = false;
    bool hayBarco = false;
}cEnemigo;

class Tablero : public BattleShipObject{
    
public:
    Tablero(Vector2D* pos, int w, int h, Texture* t, Game *game);
    ~Tablero();
    void render();
    void handleEvents(SDL_Event& event);
    bool getPuedeColocar(); 
    //SDL_Rect getRect() const;
    inline int getFilas(){return filas;};
    inline int getColumnas(){return columnas;};
    inline std::vector<std::vector<bool>> &getCasillas(){ return casillas;};
    inline std::vector<std::vector<cEnemigo>> &getCasillasEnemigo(){ return casillasEnemigo;};


    //Procesa los barcos enemigos y los coloca en una matriz para hacer comprobaciones posteriores.
    void processEnemy(MessageBarco info);

    //Procesa los ataques enemigos y representa en el tablero si has recibido un hit o no.
    void processDefense(MessageBarco info);

    //Procesa tus ataques, los envía al enemigo y representa en el tablero si has acertado o no.
    void processAttack(const Vector2D &clickPos);




private:
    int filas = 8, columnas = 10;
    std::vector<std::vector<bool>> casillas;
    std::vector<std::vector<cEnemigo>> casillasEnemigo;

    int barcosRestantes;
    Game *m_game;


};
#endif