#ifndef _SKELETON_ENEMY_H_
#define _SKELETON_ENEMY_H_

#include "enemy.h"
#include "../manager/config_manager.h"
#include "../manager/resources_manager.h"

class SkeletonEnemy : public Enemy
{
public:
	SkeletonEnemy();
	~SkeletonEnemy() = default;
};

#endif