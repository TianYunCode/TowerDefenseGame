#pragma once

#include "Timer.h"
#include "TwoVector.h"
#include "ConfigManager.h"
#include "ResourcesManager.h"

#include <SDL.h>

class Banner
{
public:
	Banner();
	~Banner() = default;

	void setCenterPosition(const TwoVector& pos);

	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

	bool checkEndDispaly();

private:
	TwoVector m_posCenter;

	TwoVector m_sizeForeground;
	TwoVector m_sizeBackground;

	SDL_Texture* m_texForeground = nullptr;
	SDL_Texture* m_texBackground = nullptr;

	Timer m_timerDisplay;
	bool m_isEndDisplay = false;
};
