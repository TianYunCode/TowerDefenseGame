#pragma once

#include "CoinManager.h"
#include "HomeManager.h"
#include "ResourcesManager.h"
#include "PlayerManager.h"

#include <SDL.h>
#include <string>
#include <SDL2_gfxPrimitives.h>

class StatusBar
{
public:
	StatusBar() = default;
	~StatusBar() = default;

	void setPosition(int x, int y);

	void onUpdate(SDL_Renderer* renderer);
	void onRender(SDL_Renderer* renderer);

private:
	const int m_sizeHeart = 32;
	const int m_widthMpBar = 200;
	const int m_heightMpBar = 20;
	const int m_widthBorderMpBar = 4;
	const SDL_Point m_offsetShadow = { 2, 2 };
	const SDL_Color m_colorTextBackground = { 175, 175, 175, 255 };
	const SDL_Color m_colorTextForeground = { 255, 255, 255, 255 };
	const SDL_Color m_colorMpBarBackground = { 48, 40, 51, 255 };
	const SDL_Color m_colorMpBarForedground = { 144, 121, 173, 255 };

private:
	SDL_Point m_position = { 0 };
	int m_widthText = 0, m_heightText = 0;
	SDL_Texture* m_texTextBackground = nullptr;
	SDL_Texture* m_texTextForeground = nullptr;
};
