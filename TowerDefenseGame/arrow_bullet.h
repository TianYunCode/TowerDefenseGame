#ifndef _ARROW_BULLET_H_
#define _ARROW_BULLET_H_

#include "bullet.h"
#include "resources_manager.h"

class ArrowBullet : public Bullet
{
public:
	ArrowBullet();
	~ArrowBullet() = default;

	void on_collide(Enemy* enemy) override;
};

#endif
