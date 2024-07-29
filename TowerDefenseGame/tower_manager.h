#ifndef _TOWER_MANAGER_H_
#define _TOWER_MANAGER_H_

#include "tower.h"
#include "tower_type.h"
#include "manager.h"
#include "archer_tower.h"
#include "axeman_tower.h"
#include "gunner_tower.h"
#include "config_manager.h"
#include "resources_manager.h"

#include <vector>

class TowerManager : public Manager<TowerManager>
{
	friend class Manager<TowerManager>;

public:
	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	double get_place_cost(TowerType type);
	double get_upgrade_cost(TowerType type);
	double get_damage_range(TowerType type);

	void place_tower(TowerType type, const SDL_Point& idx);
	void upgrade_tower(TowerType type);

protected:
	TowerManager() = default;
	~TowerManager() = default;

private:
	std::vector<Tower*> tower_list;
};

#endif
