#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <thread>
#include <string>
#include <list>

#include "Network/ClickSerializer.h"
#include "Network/ClientServer.h"

class Barco;
class Button;
class Vector2D;
class Texture;
class Tablero;
class BattleShipObject;

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int NUM_TEXTURES = 5;

// tipo enumerado de todas las texturas
enum TextureName { BOAT_PLACE, BUTTON, BOARD, HIT, NO_HIT};

// estructura simple con una cadena de caracteres del archivo, y entero de final y columnas
typedef struct {
	std::string filename;
	int cols, rows;
} TextureDescription;

// array de TextureDescription con los datos de cada textura y si es spritesheet o no
const TextureDescription TEXT_DESCR[NUM_TEXTURES] = {
	{"Imgs/place_Boat.png", 2, 1},
	{"Imgs/radio_button.png", 4, 2},
	{"Imgs/tablero.jpg", 1, 1},
    {"Imgs/tick.png", 1, 1},
    {"Imgs/cross.png", 1, 1}
};

class Game{
public:
    Game();

    // Frees media and shuts down SDL
    void closeSDL();

    void run(ChatClient& cliente);

    void render();

    void update();

    void handleEvents(ChatClient &cliente);

    void crearBarco();

    void createMessage(const setupInfo &info);

    void changeAtacar();

    void captureServerMessage(setupInfo i);

    inline bool getAttackPhase(){return attackPhase;}

    //Muestra gráficamente si el enemigo ha acertado en uno de tus barcos o no;
    void crearCasillaHitDefense(bool hit, Vector2D *pos);

    //Muestra gráficamente si has acertado en uno de los barcos del enemigo o no;
    void crearCasillaHitAttack(bool hit, Vector2D *pos);

    static void attack(Game* game);

    static void addBoat(Game* game);

    inline void setBarcoCogido() { barcoCogido = false; };

    void cambiaFase();
    void cambiaTurno();
    //comienza el juego, cambiando de fase para emezar a disparar, 
    //solo disponible una vez colocados todos los barcos
    void comienzaPartida(); 

private:

    bool quit = false;
    bool faseColocacion = true;
    bool miTurno = true;
    
    bool barcoCogido = false;
    bool messageReceived = false;

    bool attackPhase = false;
    bool setup = true;

    Tablero *gameBoard = nullptr;
    Barco* currentBoat = nullptr;
    Vector2D* v = nullptr;
    Button *testButton = nullptr;
    Button *estoyListo = nullptr; //para dar click y empezar a jugar

    Button *testButton2 = nullptr;

    setupInfo info;
    setupInfo serverInfo;

    std::list<BattleShipObject*> setupGameObjects;
    std::list<BattleShipObject*> attackGameObjects;

    Texture* arrayTex[NUM_TEXTURES];

    // The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    // The window to render
    SDL_Renderer *gRender = nullptr;

    // The image we will load and show on the screen
    SDL_Surface *gHelloWorld = NULL;
};

#endif