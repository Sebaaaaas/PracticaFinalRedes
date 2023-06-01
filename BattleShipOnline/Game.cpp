#include "Game.h"

#include "GameObjects/Barco.h"
#include "GameObjects/Button.h"
#include "Tablero.h"
#include "Texture.h"
#include "Vector2D.h"

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    gWindow = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRender, 94, 186, 125, 255);

    tableroText = new Texture(gRender, "Imgs/tablero.jpg", 1, 1);
    boatText = new Texture(gRender, "Imgs/place_Boat.png", 1, 2);
    botonTex = new Texture(gRender, "Imgs/radio_button.png", 2, 4);

    gameBoard = new Tablero(Vector2D(0, 0), SCREEN_WIDTH, SCREEN_HEIGHT, tableroText);

    v = new Vector2D(30,0);
    testButton = new Button(v, 60, 60, botonTex, addBoat, this);
}

void Game::closeSDL()
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

void Game::run(ChatClient &cliente)
{
    // INICIO DEL TABLERO REAL, 100 en X y 90 en Y
    // 460 de ancho 320 de largo
    //  46 por columna    40 por fila

    while (!quit)
    {
        handleEvents(cliente);
        update();
        render();
    }

    closeSDL();
}

void Game::render()
{
    SDL_RenderClear(gRender);

    gameBoard->render();

    if (boats.size() != 0) {
        for (auto a : boats) {
            a->render();
        }
    }

    testButton->render();

    SDL_RenderPresent(gRender);
}

void Game::update()
{
    if (currentBoat != nullptr) currentBoat->update();
    testButton->update();
}

void Game::handleEvents(ChatClient &cliente)
{
    SDL_Event e;

    messageInfo info;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                switch(e.button.button){
                case SDL_BUTTON_LEFT:
                    if (currentBoat != nullptr) currentBoat->handleEvent(info);
                    cliente.input_thread(info);
                break;
                default:
                break;
                }
            }
            else{
                testButton->handleEvents(e);
                if (currentBoat != nullptr) currentBoat->handleEvents(e);
            }
            
        }
}

void Game::crearBarco()
{
    if (!barcoCogido) {
        std::cout << boats.size() << "\n";
        currentBoat = new Barco(v , 80, 24, 2, boatText, gameBoard, this);
        boats.push_back(currentBoat);
        barcoCogido = true;
    }
}

void Game::addBoat(Game* game)
{
    game->crearBarco();
}

void Game::cambiaFase(){
    faseColocacion = !faseColocacion;
}

void Game::cambiaTurno(){
    miTurno = !miTurno;
}

void Game::comienzaPartida(){

    //if(todos los barcos estan colocados)
    //cambiaFase();

}