#pragma once

#include "GameState.h"

#include <stack>

using namespace std;

class GameStateMachine
{
	stack<GameState*> gameStates;

public:
	GameStateMachine(){};
	~GameStateMachine();

	GameState* currentState();
	void pushState(GameState* g);
	void changeState(GameState* g); //mientras no encuentre el estado, vamos quitando
	void popState();

	void update();
	void render();
	void handleEvents(SDL_Event& event);
};