#ifndef _KINNG_SLIM_ENEMY_H_
#define _KINNG_SLIM_ENEMY_H_

#include "enemy.h"
#include "../manager/config_manager.h"
#include "../manager/resources_manager.h"

class KingSlimeEnemy : public Enemy
{
public:
	KingSlimeEnemy();
	~KingSlimeEnemy() = default;
};

#endif