#ifndef _SLIM_ENEMY_H_
#define _SLIM_ENEMY_H_

#include "enemy.h"
#include "../manager/config_manager.h"
#include "../manager/resources_manager.h"

class SlimEnemy : public Enemy
{
public:
	SlimEnemy();
	~SlimEnemy() = default;
};

#endif
