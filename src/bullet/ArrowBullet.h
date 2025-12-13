#pragma once

#include "Bullet.h"
#include "ResourcesManager.h"

class ArrowBullet : public Bullet
{
public:
	ArrowBullet();
	~ArrowBullet() = default;

	void onCollide(Enemy* enemy) override;
};
