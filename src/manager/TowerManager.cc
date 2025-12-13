#include "TowerManager.h"

void TowerManager::onUpdate(double delta)
{
	for (Tower* tower : m_towerList)
	{
		tower->onUpdate(delta);
	}
}

void TowerManager::onRender(SDL_Renderer* renderer)
{
	for (Tower* tower : m_towerList)
	{
		tower->onRender(renderer);
	}
}

double TowerManager::getPlaceCost(TowerType type)
{
	static ConfigManager* instance = ConfigManager::instance();

	switch (type)
	{
	case Archer:
		return instance->m_archerTemplate.m_cost[instance->m_levelArcher];
		break;
	case Axeman:
		return instance->m_axemanTemplate.m_cost[instance->m_levelAxeman];
		break;
	case Gunner:
		return instance->m_gunnerTemplate.m_cost[instance->m_levelGunner];
		break;
	}

	return 0;
}

double TowerManager::getUpgradeCost(TowerType type)
{
	static ConfigManager* instance = ConfigManager::instance();

	switch (type)
	{
	case Archer:
		return instance->m_levelArcher == 9 ? -1 : instance->m_archerTemplate.m_upgradeCost[instance->m_levelArcher];
		break;
	case Axeman:
		return instance->m_levelAxeman == 9 ? -1 : instance->m_axemanTemplate.m_upgradeCost[instance->m_levelAxeman];
		break;
	case Gunner:
		return instance->m_levelGunner == 9 ? -1 : instance->m_gunnerTemplate.m_upgradeCost[instance->m_levelGunner];
		break;
	}

	return 0;
}

double TowerManager::getDamageRange(TowerType type)
{
	static ConfigManager* instance = ConfigManager::instance();

	switch (type)
	{
	case Archer:
		return instance->m_archerTemplate.m_viewRange[instance->m_levelArcher];
		break;
	case Axeman:
		return instance->m_axemanTemplate.m_viewRange[instance->m_levelAxeman];
		break;
	case Gunner:
		return instance->m_gunnerTemplate.m_viewRange[instance->m_levelGunner];
		break;
	}

	return 0;
}

void TowerManager::placeTower(TowerType type, const SDL_Point& idx)
{
	Tower* tower = nullptr;

	switch (type)
	{
	case Archer:
		tower = new ArcherTower();
		break;
	case Axeman:
		tower = new AxemanTower();
		break;
	case Gunner:
		tower = new GunnerTower();
		break;
	default:
		tower = new ArcherTower();
		break;
	}

	static TwoVector position;
	static const SDL_Rect& rect = ConfigManager::instance()->m_rectTileMap;

	position.m_x = rect.x + idx.x * SIZE_TILE + SIZE_TILE / 2;
	position.m_y = rect.y + idx.y * SIZE_TILE + SIZE_TILE / 2;
	tower->setPosition(position);
	m_towerList.push_back(tower);

	ConfigManager::instance()->m_map.placeTower(idx);

	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	Mix_PlayChannel(-1, soundPool.find(ResID::Sound_PlaceTower)->second, 0);
}

void TowerManager::upgradeTower(TowerType type)
{
	static ConfigManager* instance = ConfigManager::instance();

	switch (type)
	{
	case Archer:
		instance->m_levelArcher = instance->m_levelArcher >= 9 ? 9 : instance->m_levelArcher + 1;
		break;
	case Axeman:
		instance->m_levelAxeman = instance->m_levelAxeman >= 9 ? 9 : instance->m_levelAxeman + 1;
		break;
	case Gunner:
		instance->m_levelGunner = instance->m_levelGunner >= 9 ? 9 : instance->m_levelGunner + 1;
		break;
	}

	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	Mix_PlayChannel(-1, soundPool.find(ResID::Sound_TowerLevelUp)->second, 0);
}