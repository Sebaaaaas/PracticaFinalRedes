#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <thread>
#include <list>

#include "Network/ClickSerializer.h"
#include "Network/ClientServer.h"

class Barco;
class Button;
class Vector2D;
class Texture;
class Tablero;
class GameStateMachine;
class GameState;

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Game{
public:
    Game();

    // Frees media and shuts down SDL
    void closeSDL();

    void run(ChatClient& cliente);

    void render();

    void update();

    void handleEvents(ChatClient &cliente);

    // static void createBoat();

private:

    bool quit = false;

    GameStateMachine* gsMachine = nullptr;

    Tablero *gameBoard = nullptr;
    Barco *b = nullptr;
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