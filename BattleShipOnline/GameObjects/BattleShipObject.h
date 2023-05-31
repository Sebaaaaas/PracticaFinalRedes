#pragma once

#include "GameObject.h"

class Vector2D;
class Texture;

class BattleShipObject : public GameObject
{
protected:
	int w = 0, h = 0;
	Vector2D* pos = nullptr;
	Texture* tex = nullptr;
	SDL_Rect destRect;
public:
	BattleShipObject(Vector2D* pos_, int w_, int h_, Texture* tex_);
	virtual ~BattleShipObject();

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

	virtual SDL_Rect getRect();
};

