#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_

#include "bullet.h"
#include "manager.h"
#include "arrow_bullet.h"
#include "axe_bullet.h"
#include "shell_bullet.h"
#include "bullet_type.h"

#include <vector>

//子弹管理器
class BulletManager : public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:
	typedef vector<Bullet*> BulletList;

public:
	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	BulletList& get_bullet_list();

	//射击子弹
	void fire_bullet(BulletType type, const TwoVector& position, const TwoVector& velocity, double damage);

protected:
	BulletManager() = default;
	~BulletManager();

private:
	BulletList bullet_list; //子弹列表
};

#endif