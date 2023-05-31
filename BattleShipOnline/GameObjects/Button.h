#pragma once

#include "../Game.h"
#include "BattleShipObject.h"
#include "../Vector2D.h"

class Game;

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};

typedef void CallBack(Game* game);

class Button : public BattleShipObject
{
	
public:
	Button(Vector2D* p, int w, int h, Texture* t, CallBack func, Game* game);
	~Button();
	
	void checkBounds();
	
	void render();
	void update();
	void handleEvents(SDL_Event& event);

	

private:
	bool clicked = false;
	bool m_bReleased = false;
	button_state m_currentFrame;
	CallBack* callbackFunc;
	Game* m_game = nullptr;

	SDL_Point pMousePos;

};
