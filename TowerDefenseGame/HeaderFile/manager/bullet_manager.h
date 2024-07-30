#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_

#include "../bullet/bullet.h"
#include "manager.h"
#include "../bullet/arrow_bullet.h"
#include "../bullet/axe_bullet.h"
#include "../bullet/shell_bullet.h"
#include "../bullet/bullet_type.h"

#include <vector>

class BulletManager : public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:
	typedef std::vector<Bullet*> BulletList;

public:
	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	BulletList& get_bullet_list();

	void fire_bullet(BulletType type, const Vector2& position, const Vector2& velocity, double damage);

protected:
	BulletManager() = default;
	~BulletManager();

private:
	BulletList bullet_list;
};

#endif