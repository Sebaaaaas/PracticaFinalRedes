/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include "tablero.h"
#include "ClickSerializer.h"
#include "ClientServer.h"
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void closeSDL();

void run();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;


int main( int argc, char* args[] )
{
    
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            run();
        }
    }


    //Free resources and close SDL
    closeSDL();

    return 0;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP( "Imgs/test.bmp" );
	if( gHelloWorld == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "Imgs/test.bmp", SDL_GetError() );
		success = false;
	}

    return success;
}

void closeSDL()
{
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void run(){
	int fd = open("binarios", O_CREAT | O_RDWR | O_TRUNC, 0644);
	close(fd);
	Click* test_deserialize = new Click("CLICK", 0,0);
	Click* test_click = new Click("CLICK", 0,0);

	bool quit = false;

	SDL_Event e;

	while(!quit){
		while(SDL_PollEvent(&e) != 0){
				if(e.type ==SDL_QUIT){
					quit = true;
				}
				else if(e.type == SDL_MOUSEBUTTONDOWN){
					if(e.button.button == SDL_BUTTON_LEFT){
						int x, y;
						SDL_GetMouseState(&x, &y);
						test_click->setClickPos(x, y);
						test_click->toFileAndBack(test_deserialize);
					}
				}
				
		}

		//Apply the image
		SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

		//Update the surface
		SDL_UpdateWindowSurface( gWindow );
	}
}