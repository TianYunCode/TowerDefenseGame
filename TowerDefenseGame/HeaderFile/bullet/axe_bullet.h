#ifndef _AXE_BULLET_H_
#define _AXE_BULLET_H_

#include "bullet.h"
#include "../manager/resources_manager.h"

class AxeBullet : public Bullet
{
public:
	AxeBullet();
	~AxeBullet() = default;

	void on_collide(Enemy* enemy) override;
};

#endif
