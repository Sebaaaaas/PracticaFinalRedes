#include "Button.h"

#include "../Texture.h"

Button::Button(Vector2D* p, int w, int h, Texture* t) : BattleShipObject(p, w, h, t){
	m_currentFrame = MOUSE_OUT;
	pMousePos = { 0, 0 };
}

Button::~Button() {
}

void Button::render()
{
	if(m_currentFrame == MOUSE_OVER)
		tex->renderFrame(destRect, 0, 3);	
	else if(m_currentFrame == CLICKED)
		tex->renderFrame(destRect, 1, 1);
	else
		tex->renderFrame(destRect, 0, 1);

}
void Button::update()
{
	
	if (pMousePos.x < (this->destRect.x + this->destRect.w)
		&& pMousePos.x > this->destRect.x
		&& pMousePos.y < (this->destRect.y + this->destRect.h)
		&& pMousePos.y > this->destRect.y)
	{
		m_currentFrame = MOUSE_OVER;
		if (clicked && m_bReleased)
		{
			m_currentFrame = CLICKED;
			
			m_bReleased = false;
			clicked = false;
		}
		else {
			m_bReleased = true;
		}

	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void Button::handleEvents(SDL_Event& event) {

	int x, y;
    SDL_GetMouseState(&x, &y);
	pMousePos = { x, y};

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
		clicked = true;
	}
	else {
		clicked = false;
	}
}