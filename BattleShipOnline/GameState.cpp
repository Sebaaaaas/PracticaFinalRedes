#include "GameState.h"

GameState::GameState() {

}

void GameState::update()
{
	for (auto i : gameObjects)
		i->update();
}

void GameState::render()
{
	for (auto i : gameObjects)
		i->render();
}

void GameState::handleEvents(SDL_Event& event)
{
	for (auto i : gameObjects)
		i->handleEvents(event);
}
