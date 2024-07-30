#ifndef _GOBLIN_ENEMY_H_
#define _GOBLIN_ENEMY_H_

#include "../enemy/enemy.h"
#include "../manager/config_manager.h"
#include "../manager/resources_manager.h"

class GoblinEnemy : public Enemy
{
public:
	GoblinEnemy();
	~GoblinEnemy() = default;
};

#endif