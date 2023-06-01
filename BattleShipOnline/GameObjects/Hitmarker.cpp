#include "Hitmarker.h"
#include "../Texture.h"

Hitmarker::Hitmarker(Vector2D *p, int w, int h, Texture *t) : BattleShipObject(p, w, h, t)
{

}

Hitmarker::~Hitmarker()
{
}

void Hitmarker::render()
{
    tex->render(getRect());
}
