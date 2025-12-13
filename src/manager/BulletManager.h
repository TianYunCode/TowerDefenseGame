#pragma once

#include "Bullet.h"
#include "Manager.h"
#include "ArrowBullet.h"
#include "AxeBullet.h"
#include "ShellBullet.h"
#include "BulletType.h"

#include <vector>

class BulletManager : public Manager<BulletManager>
{
	friend class Manager<BulletManager>;

public:
	typedef std::vector<Bullet*> BulletList;

public:
	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

	BulletList& getBulletList();

	void fireBullet(BulletType type, const TwoVector& position, const TwoVector& velocity, double damage);

protected:
	BulletManager() = default;
	~BulletManager();

private:
	BulletList m_bulletList;
};
