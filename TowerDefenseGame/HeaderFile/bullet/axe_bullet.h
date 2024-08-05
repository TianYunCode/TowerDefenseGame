#ifndef _AXE_BULLET_H_
#define _AXE_BULLET_H_

#include "bullet.h"
#include "resources_manager.h"

//斧头类（斧头兵扔出的兵器）
class AxeBullet : public Bullet
{
public:
	AxeBullet();
	~AxeBullet() = default;

	void on_collide(Enemy* enemy) override;
};

#endif