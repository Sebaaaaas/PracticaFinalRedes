#pragma once

#include "BattleShipObject.h"


class Game;


class Hitmarker : public BattleShipObject
{
	
public:
	Hitmarker(Vector2D* p, int w, int h, Texture* t);
	~Hitmarker();

	void render();
};