#pragma once

#include "Panel.h"
#include "TowerManager.h"
#include "ResourcesManager.h"

class UpgradePanel : public Panel
{
public:
	UpgradePanel();
	~UpgradePanel() = default;

	void onUpdate(SDL_Renderer* renderer);

protected:
	void onClickTopArea() override;
	void onClickLeftArea() override;
	void onClickRightArea() override;
};
