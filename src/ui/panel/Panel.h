#pragma once

#include "Tile.h"
#include "ResourcesManager.h"

#include <SDL.h>
#include <string>

class Panel
{
public:
	Panel();
	~Panel();

	void show();

	void setIdxTile(const SDL_Point& idx);
	void setCenterPos(const SDL_Point& pos);

	void onInput(const SDL_Event& event);
	virtual void onUpdate(SDL_Renderer* renderer);
	virtual void onRender(SDL_Renderer* renderer);

protected:
	enum class HoveredTarget
	{
		None,
		Top,
		Left,
		Right
	};

protected:
	bool m_visible = false;
	SDL_Point m_idxTileSelected;
	SDL_Point m_centerPos = { 0 };
	SDL_Texture* m_texIdle = nullptr;
	SDL_Texture* m_texHoveredTop = nullptr;
	SDL_Texture* m_texHoveredLeft = nullptr;
	SDL_Texture* m_texHoveredRight = nullptr;
	SDL_Texture* m_texSelectCursor = nullptr;
	int m_valTop = 0, m_valLeft = 0, m_valRight = 0;
	HoveredTarget m_hoveredTarget = HoveredTarget::None;

protected:
	virtual void onClickTopArea() = 0;
	virtual void onClickLeftArea() = 0;
	virtual void onClickRightArea() = 0;

private:
	const int m_sizeButton = 48;
	const int m_width = 144, m_height = 144;
	const SDL_Point m_offsetTop = { 48, 6 };
	const SDL_Point m_offsetLeft = { 8, 80 };
	const SDL_Point m_offsetRight = { 90, 80 };
	const SDL_Point m_offsetShadow = { 3, 3 };
	const SDL_Color m_colorTextBackground = { 175, 175, 175, 255 };
	const SDL_Color m_colorTextForeground = { 255, 255, 255, 255 };

	int m_widthText = 0, m_heightText = 0;
	SDL_Texture* m_texTextBackground = nullptr;
	SDL_Texture* m_texTextForeground = nullptr;
};
