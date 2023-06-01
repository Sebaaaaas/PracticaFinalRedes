#include "Button.h"

#include "../Texture.h"

Button::Button(Vector2D* p, int w, int h, std::pair<int, int> normalTex_, std::pair<int, int> mouseOverTex_, Texture* t, CallBack* func, Game* game) : BattleShipObject(p, w, h, t), normalTex(normalTex_), mouseOverTex(mouseOverTex_){
	m_currentFrame = MOUSE_OUT;
	pMousePos = { 0, 0 };
	callbackFunc = func;
	m_game = game;
}

Button::~Button() {
}

void Button::render()
{
	if(m_currentFrame == MOUSE_OVER)
		tex->renderFrame(destRect, mouseOverTex.first, mouseOverTex.second);	
	else if(m_currentFrame == CLICKED)
		tex->renderFrame(destRect, mouseOverTex.first, mouseOverTex.second);
	else
		tex->renderFrame(destRect, normalTex.first, normalTex.second);

}
void Button::update()
{
	checkBounds();
}

void Button::handleEvents(SDL_Event& event) {

	int x, y;
    SDL_GetMouseState(&x, &y);
	pMousePos = { x, y};

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && m_currentFrame == MOUSE_OVER) {
		clicked = true;
		callbackFunc(m_game);
	}
	else {
		clicked = false;
	}
}

void Button::checkBounds()
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