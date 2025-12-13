#pragma once

#include "Tower.h"
#include "TowerType.h"
#include "Manager.h"
#include "ArcherTower.h"
#include "AxemanTower.h"
#include "GunnerTower.h"
#include "ConfigManager.h"
#include "ResourcesManager.h"

#include <vector>

class TowerManager : public Manager<TowerManager>
{
	friend class Manager<TowerManager>;

public:
	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

	double getPlaceCost(TowerType type);
	double getUpgradeCost(TowerType type);
	double getDamageRange(TowerType type);

	void placeTower(TowerType type, const SDL_Point& idx);
	void upgradeTower(TowerType type);

protected:
	TowerManager() = default;
	~TowerManager() = default;

private:
	std::vector<Tower*> m_towerList;
};
