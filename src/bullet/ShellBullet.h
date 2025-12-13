#pragma once

#include "Bullet.h"
#include "ResourcesManager.h"

class ShellBullet : public Bullet
{
public:
	ShellBullet();
	~ShellBullet() = default;

	void onUpdate(double delta) override;
	void onRender(SDL_Renderer* renderer) override;
	void onCollide(Enemy* enemy) override;

private:
	Animation m_animationExplode;
};
