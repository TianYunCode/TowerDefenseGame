#pragma once

#include "Panel.h"
#include "CoinManager.h"
#include "TowerManager.h"
#include "ResourcesManager.h"

#include <SDL2_gfxPrimitives.h>

class PlacePanel : public Panel
{
public:
	PlacePanel();
	~PlacePanel() = default;

	void onUpdate(SDL_Renderer* renderer) override;
	void onRender(SDL_Renderer* renderer) override;

protected:
	void onClickTopArea() override;
	void onClickLeftArea() override;
	void onClickRightArea() override;

private:
	const SDL_Color m_colorRegionFrame = { 30, 80, 162, 175 };
	const SDL_Color m_colorRegionContent = { 0, 149, 217, 75 };

private:
	int m_regTop = 0, m_regLeft = 0, m_regRight = 0;
};
