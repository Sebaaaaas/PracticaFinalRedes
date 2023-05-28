#pragma once

#include <SDL2/SDL.h>

class GameObject
{
public:
	virtual ~GameObject(){};
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvents(SDL_Event& event) = 0;
};

