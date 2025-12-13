#pragma once

#include "Facing.h"
#include "TwoVector.h"
#include "Animation.h"
#include "TowerType.h"
#include "EnemyManager.h"
#include "BulletManager.h"

class Tower
{
public:
	Tower();
	~Tower() = default;

	void setPosition(const TwoVector& position);

	const TwoVector& getSize() const;
	const TwoVector& getPosition() const;

	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

protected:
	TwoVector m_size;

	Animation m_animIdleUp;
	Animation m_animIdleDown;
	Animation m_animIdleLeft;
	Animation m_animIdleRight;
	Animation m_animFireUp;
	Animation m_animFireDown;
	Animation m_animFireLeft;
	Animation m_animFireRight;

	TowerType m_towerType = TowerType::Archer;

	double m_fireSpeed = 0;
	BulletType m_bulletType = BulletType::Arrow;

private:
	Timer m_timerFire;
	TwoVector m_position;
	bool m_canFire = true;
	Facing m_facing = Facing::Right;
	Animation* m_animCurrent = &m_animIdleRight;

private:
	void updateIdleAnimation();
	void updateFireAnimation();

	Enemy* findTargetEnemy();

	void onFire();
};
