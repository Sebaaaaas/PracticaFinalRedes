#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <thread>

#include "Tablero.h"
#include "Texture.h"
#include "Barco.h"
#include "Texture.h"
#include "Vector2D.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "Network/ClickSerializer.h"
#include "Network/ClientServer.h"
#include "GameObjects/Button.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Button;

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

    static void addBoat(Game* game);

    inline void setBarcoCogido() {barcoCogido = false;};

private:

    bool quit = false;
    bool barcoCogido = false;

    GameStateMachine* gsMachine = nullptr;

    Tablero *gameBoard = nullptr;
    Barco *b = nullptr;
    Barco* currentBoat = nullptr;
    Vector2D* v = nullptr;
    Button *testButton = nullptr;

    std::list<Barco*> boats;
    // The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    // The window to render
    SDL_Renderer *gRender = nullptr;

    // The image we will load and show on the screen
    SDL_Surface *gHelloWorld = NULL;

    Texture *tableroText = nullptr;
    Texture *boatText = nullptr;
    Texture *botonTex = nullptr;
};

#endif