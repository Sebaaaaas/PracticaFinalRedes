#pragma once

#include "BattleShipObject.h"
#include "../Vector2D.h"

// class Game;

// using CallBackOnClick = void(Game* game);

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};

class Button : public BattleShipObject
{
	
public:
	Button(Vector2D* p, int w, int h, Texture* t);
	~Button();

	void render();
	void update();
	void handleEvents(SDL_Event& event);

private:
	bool clicked = false;
	bool m_bReleased = false;
	button_state m_currentFrame;

	SDL_Point pMousePos;
	// CallBackOnClick* cbOnClick = nullptr;

};
