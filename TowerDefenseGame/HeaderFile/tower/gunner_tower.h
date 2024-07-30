#ifndef _GUNNER_TOWER_H_
#define _GUNNER_TOWER_H_

#include "../tower.h"
#include "../manager/resources_manager.h"

class GunnerTower : public Tower
{
public:
	GunnerTower();
	~GunnerTower() = default;
};

#endif