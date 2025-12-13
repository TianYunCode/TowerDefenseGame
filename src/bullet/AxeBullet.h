#pragma once

#include "Bullet.h"
#include "ResourcesManager.h"

class AxeBullet : public Bullet
{
public:
	AxeBullet();
	~AxeBullet() = default;

	void onCollide(Enemy* enemy) override;
};
