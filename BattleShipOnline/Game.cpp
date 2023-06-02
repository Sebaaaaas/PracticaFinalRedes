#include "Game.h"

#include "GameObjects/Barco.h"
#include "GameObjects/Button.h"
#include "GameObjects/Tablero.h"
#include "GameObjects/Hitmarker.h"
#include "Texture.h"
#include "Vector2D.h"

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    gWindow = SDL_CreateWindow("BattleShip", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRender, 94, 186, 125, 255);

    for (int i = 0; i < NUM_TEXTURES; ++i) { 
		const TextureDescription& desc = TEXT_DESCR[i];
		arrayTex[i] = new Texture(gRender, desc.filename, desc.rows, desc.cols);

	}

    gameBoard = new Tablero(new Vector2D(0, 0), 640, 480, arrayTex[BOARD], this);
    setupGameObjects.push_back(gameBoard);
    attackGameObjects.push_back(gameBoard);

    v = new Vector2D(30,0);
    testButton = new Button(v, 60, 60, {0,1}, {0,3}, arrayTex[BUTTON], addBoat, this);

    v = new Vector2D(200, 0);
    testButton2 = new Button(v, 60, 60, {0,1}, {0,3}, arrayTex[BUTTON], readyUpForGame, this);
    attackGameObjects.push_back(testButton2);

    setupGameObjects.push_back(testButton);
    setupGameObjects.push_back(testButton2);

    //Botones de colocar barcos de distintos tamaños

    int bw = 60, bh = 44;
    int lonAct = bw;
    std::pair<int, int> texPos = {0,1};
    std::pair<int, int> texPos2 = {0,0};

    // lonAct = bw * barcosAPoner.front();
    // v = new Vector2D(SCREEN_WIDTH - lonAct - 20, bh + 100);
    // botonBarco = new Button(v, lonAct, bh, texPos, texPos2, arrayTex[BOAT_PLACE], addBoat, this);
  
    // setupGameObjects.push_back(botonBarco);

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
        if(messageReceived){
            messageReceived = false;
            //std::cout << "Game.cpp X : "<< serverInfo.pos.getX() << " Y : " << serverInfo.pos.getY() << "\n";
            if(setup){
                gameBoard->processEnemy(serverInfo);
            }
            else if(!setup && !attackPhase){
                std::cout << "serverInfo X " << serverInfo.pos.getX() << " Y " << serverInfo.pos.getY() << "\n";
                gameBoard->processDefense(serverInfo);
            }
        }
        handleEvents(cliente);
        update();
        render();
    }

    closeSDL();
}

void Game::render()
{
    SDL_RenderClear(gRender);

    if(attackPhase){
        for(auto g: attackGameObjects){
            g->render();
        }
    }
    else{
        for(auto g: setupGameObjects){
            g->render();
        }
    }

    SDL_RenderPresent(gRender);
}

void Game::update()
{
    if(attackPhase){
        for(auto g: attackGameObjects){
            g->update();
        }
    }
    else{
        for(auto g: setupGameObjects){
            g->update();
        }
    }

    //cambiamos de fase una vez pulsado el boton con todos los barcos colocados
    if(readyForNextPhase && barcosAPoner.empty()){
        changeAtacar();
    }

}

void Game::handleEvents(ChatClient &cliente)
{
    SDL_Event e;

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            // else{
            //     for(auto g: setupGameObjects){
            //         g->handleEvents(e);
            //         cliente.input_thread(info);
            //     }
            // }
            else if(attackPhase){
                for(auto g: attackGameObjects){
                    g->handleEvents(e);
                    cliente.input_thread(info);
                }
            }
            else if(!attackPhase){
                for(auto g: setupGameObjects){
                    g->handleEvents(e);
                    cliente.input_thread(info);
                }
            }
            
        }
}

void Game::crearBarco()
{
    if (!barcoCogido) {
        currentBoat = new Barco(v , 40, 24, barcosAPoner.front(), arrayTex[BOAT_PLACE], gameBoard, this);
        setupGameObjects.push_back(currentBoat);
        barcoCogido = true;

        if(!barcosAPoner.empty())
            barcosAPoner.pop_front();
    }
}

void Game::addBoat(Game* game)
{
    game->crearBarco();
}


void Game::createMessage(const setupInfo &boatInfo)
{
  info = boatInfo;
}

void Game::changeAtacar(){
    setup = false;
    attackPhase = !attackPhase;
    if(!attackPhase){
        std::cout << "Estas en defensa \n";
    }
    else{
        std::cout << "Estas en ataque \n";
    }
}

void Game::cambiaFase(){
    // faseColocacion = !faseColocacion;
    readyForNextPhase = true;

}

void Game::cambiaTurno(){
    miTurno = !miTurno;
}

void Game::readyUpForGame(Game* game){
    game->cambiaFase();
}

void Game::captureServerMessage(setupInfo i)
{
    std::cout << "ServerMessage X " << i.pos.getX() << " Y " << i.pos.getY() << "\n" ; 
    serverInfo = i;
    messageReceived = true;
}

void Game::crearCasillaHitDefense(bool hit, Vector2D* pos)
{
    //currentBoat = new Barco(v , 80, 24, 2, arrayTex[BOAT_PLACE], gameBoard, this);
    if(hit){
        setupGameObjects.push_back(new Hitmarker(pos, PIXELES_COLUMNA, PIXELES_FILA,arrayTex[HIT]));
    }
    else{
        setupGameObjects.push_back(new Hitmarker(pos, PIXELES_COLUMNA, PIXELES_FILA,arrayTex[NO_HIT]));
    }
}

void Game::crearCasillaHitAttack(bool hit, Vector2D *pos)
{
    if(hit){
        attackGameObjects.push_back(new Hitmarker(pos, PIXELES_COLUMNA, PIXELES_FILA,arrayTex[HIT]));
    }
    else{
        attackGameObjects.push_back(new Hitmarker(pos, PIXELES_COLUMNA, PIXELES_FILA,arrayTex[NO_HIT]));
    }
}

void Game::attack(Game *game)
{
    game->changeAtacar();
}
