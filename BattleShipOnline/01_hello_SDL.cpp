 /*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
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

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void closeSDL();

void run();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The window to render
SDL_Renderer *gRender = nullptr;

// The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;

Texture *tableroText = nullptr;
Texture *boatText = nullptr;
Texture *botonTex = nullptr;

GameStateMachine* gsMachine = nullptr;

int main(int argc, char *args[])
{

    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            run();
        }
    }

    // Free resources and close SDL
    closeSDL();

    return 0;
}

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("BattleShip Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Get window surface
            // gScreenSurface = SDL_GetWindowSurface( gWindow );
            gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(gRender, 94, 186, 125, 255);
        }
    }

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load splash image
    gHelloWorld = SDL_LoadBMP("Imgs/test.bmp");
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "Imgs/test.bmp", SDL_GetError());
        success = false;
    }
    tableroText = new Texture(gRender, "Imgs/tablero.jpg", 1, 1);
    boatText = new Texture(gRender, "Imgs/place_Boat.png", 1, 2);
    botonTex = new Texture(gRender, "Imgs/radio_button.png", 2, 4);


    return success;
}

void closeSDL()
{
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

void run()
{
    Tablero *t = new Tablero(Vector2D(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT, tableroText);
    Barco *b = new Barco(Vector2D(0, 0), 80, 24, boatText, t);

    Vector2D* v = new Vector2D(30,0);
    Button *testButton = new Button(v, 60, 60, botonTex);
    // INICIO DEL TABLERO REAL, 100 en X y 90 en Y
    // 460 de ancho 320 de largo
    //  46 por columna    40 por fila

    int fd = open("binarios", O_CREAT | O_RDWR | O_TRUNC, 0644);
    close(fd);
    
    Click *test_deserialize = new Click("CLICK", 0, 0);
    Click *test_click = new Click("CLICK", 0, 0);

    bool quit = false;

    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                switch(e.button.button){
                case SDL_BUTTON_LEFT:
                    b->handleEvent();
                break;
                default:
                break;
                }
            }
            else
                testButton->handleEvents(e);
            
            
        }

        b->update();
        testButton->update();

        SDL_RenderClear(gRender);

        t->render();
        b->render();

        testButton->render();

        SDL_RenderPresent(gRender);
        // //Apply the image
        // SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

        // //Update the surface
        // SDL_UpdateWindowSurface( gWindow );
    }
}