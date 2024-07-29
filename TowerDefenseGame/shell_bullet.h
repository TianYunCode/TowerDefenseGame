#ifndef _SHELL_BULLET_H_
#define _SHELL_BULLET_H_

#include "bullet.h"
#include "resources_manager.h"

class ShellBullet : public Bullet
{
public:
	ShellBullet();
	~ShellBullet() = default;

	void on_update(double delta) override;
	void on_render(SDL_Renderer* renderer) override;
	void on_collide(Enemy* enemy) override;

private:
	Animation animation_explode;
};

#endif
