#pragma once

#include "BattleShipObject.h"
#include "../Vector2D.h"
#include <utility>

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
	Button(Vector2D* p, int w, int h, std::pair<int, int> normalTex, std::pair<int, int> mouseOverTex, Texture* t, CallBack func, Game* game);
	~Button();

	void checkBounds();

	void render();
	void update();
	void handleEvents(SDL_Event& event);

	inline Texture* returnTex(){ return tex;}

private:
	bool clicked = false;
	bool m_bReleased = false;
	button_state m_currentFrame;

	CallBack* callbackFunc = nullptr;
	Game* m_game = nullptr;

	SDL_Point pMousePos;

	std::pair<int,int> normalTex;
	std::pair<int,int> mouseOverTex;


};
