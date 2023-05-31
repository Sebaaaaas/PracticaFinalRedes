#include "BattleShipObject.h"

#include "../Vector2D.h"
#include "../Texture.h"

BattleShipObject::BattleShipObject(Vector2D* pos_, int w_, int h_, Texture* tex_) 
: pos(pos_), w(w_), h(h_), tex(tex_){

	destRect.w = w; destRect.h = h;
	destRect.x = pos->getX(); destRect.y = pos->getY();

}

BattleShipObject::~BattleShipObject(){
	delete pos; pos = nullptr;
}

void BattleShipObject::render()
{
	tex->render(destRect);
}

void BattleShipObject::update()
{
	destRect.x = pos->getX(); destRect.y = pos->getY();
}

void BattleShipObject::handleEvents(SDL_Event& event)
{
}

SDL_Rect BattleShipObject::getRect(){
	SDL_Rect rect;
	rect.x = pos->getX(); rect.y = pos->getY();
	rect.w = w, rect.h = h;

	return rect;
}


