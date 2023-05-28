#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine() {
	while (!gameStates.empty()) {
		delete gameStates.top();
		gameStates.pop();
	}
}

GameState* GameStateMachine::currentState()
{
	return gameStates.top();
}

void GameStateMachine::pushState(GameState* g)
{
	gameStates.push(g);
}

void GameStateMachine::changeState(GameState* g)
{
	while (!gameStates.empty() && currentState() != g) {
		popState();
	}

	pushState(g);
}

void GameStateMachine::popState()
{
	if (!gameStates.empty()) {
		delete gameStates.top();
		gameStates.pop();
	}
}

void GameStateMachine::update()
{
	if (!gameStates.empty()) {
		gameStates.top()->update();
	}
}

void GameStateMachine::render()
{
	if (!gameStates.empty()) {
		gameStates.top()->render();
	}
}

void GameStateMachine::handleEvents(SDL_Event& event) {
	if (!gameStates.empty()) {
		gameStates.top()->handleEvents(event);
	}
}