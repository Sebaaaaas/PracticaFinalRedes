#pragma once

#include "GameObjects/GameObject.h"

#include <list>

using namespace std;

class GameState
{
protected:
	list<GameObject*> gameObjects;
	bool exitingState = false; //para cambiar de estado tras un bucle de juego y no destruir los gameObjects demasiado pronto

public:
	//GameState(Game* game_);

	virtual ~GameState() {
		clearAllObjects();	
	};

	virtual void update();

	virtual void render();

	virtual void handleEvents(SDL_Event& event);

	void clearAllObjects() {
		for (auto it : gameObjects) {
			delete it; it = nullptr;
		}

		gameObjects.clear();
	};

};

