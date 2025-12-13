#include "Tower.h"

Tower::Tower()
{
	m_timerFire.setOneShot(true);
	m_timerFire.setOnTimeout([&]() { m_canFire = true; });

	m_animIdleUp.setLoop(true);
	m_animIdleUp.setInterval(0.2);
	m_animIdleDown.setLoop(true);
	m_animIdleDown.setInterval(0.2);
	m_animIdleLeft.setLoop(true);
	m_animIdleLeft.setInterval(0.2);
	m_animIdleRight.setLoop(true);
	m_animIdleRight.setInterval(0.2);

	m_animFireUp.setLoop(false);
	m_animFireUp.setInterval(0.2);
	m_animFireUp.setOnFinished([&]() { updateIdleAnimation(); });

	m_animFireDown.setLoop(false);
	m_animFireDown.setInterval(0.2);
	m_animFireDown.setOnFinished([&]() { updateIdleAnimation(); });

	m_animFireLeft.setLoop(false);
	m_animFireLeft.setInterval(0.2);
	m_animFireLeft.setOnFinished([&]() { updateIdleAnimation(); });

	m_animFireRight.setLoop(false);
	m_animFireRight.setInterval(0.2);
	m_animFireRight.setOnFinished([&]() { updateIdleAnimation(); });
}

void Tower::setPosition(const TwoVector& position)
{
	this->m_position = position;
}

const TwoVector& Tower::getSize() const
{
	return m_size;
}

const TwoVector& Tower::getPosition() const
{
	return m_size;
}

void Tower::onUpdate(double delta)
{
	m_timerFire.onUpdate(delta);
	m_animCurrent->onUpdate(delta);

	if (m_canFire)
	{
		onFire();
	}
}

void Tower::onRender(SDL_Renderer* renderer)
{
	static SDL_Point point;

	point.x = (int)(m_position.m_x - m_size.m_x / 2);
	point.y = (int)(m_position.m_y - m_size.m_y / 2);

	m_animCurrent->onRender(renderer, point);
}

void Tower::updateIdleAnimation()
{
	switch (m_facing)
	{
	case Left:
		m_animCurrent = &m_animIdleLeft;
		break;
	case Right:
		m_animCurrent = &m_animIdleRight;
		break;
	case Up:
		m_animCurrent = &m_animIdleUp;
		break;
	case Down:
		m_animCurrent = &m_animIdleDown;
		break;
	}
}

void Tower::updateFireAnimation()
{
	switch (m_facing)
	{
	case Left:
		m_animCurrent = &m_animFireLeft;
		break;
	case Right:
		m_animCurrent = &m_animFireRight;
		break;
	case Up:
		m_animCurrent = &m_animFireUp;
		break;
	case Down:
		m_animCurrent = &m_animFireDown;
		break;
	}
}

Enemy* Tower::findTargetEnemy()
{
	double process = -1;
	double viewRange = 0;
	Enemy* enemyTarget = nullptr;

	static ConfigManager* instance = ConfigManager::instance();

	switch (m_towerType)
	{
	case Archer:
		viewRange = instance->m_archerTemplate.m_viewRange[instance->m_levelArcher];
		break;
	case Axeman:
		viewRange = instance->m_axemanTemplate.m_viewRange[instance->m_levelAxeman];
		break;
	case Gunner:
		viewRange = instance->m_gunnerTemplate.m_viewRange[instance->m_levelGunner];
		break;
	}

	EnemyManager::EnemyList& enemyList = EnemyManager::instance()->getEnemyList();

	for (Enemy* enemy : enemyList)
	{
		if ((enemy->getPosition() - m_position).length() <= viewRange * SIZE_TILE)
		{
			double newProcess = enemy->getRouteProcess();
			if (newProcess > process)
			{
				enemyTarget = enemy;
				process = newProcess;
			}
		}
	}

	return enemyTarget;
}

void Tower::onFire()
{
	Enemy* targetEnemy = findTargetEnemy();

	if (!targetEnemy)
	{
		return;
	}

	m_canFire = false;
	static ConfigManager* instance = ConfigManager::instance();
	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	double interval = 0, damage = 0;
	switch (m_towerType)
	{
	case Archer:
		interval = instance->m_archerTemplate.m_interval[instance->m_levelArcher];
		damage = instance->m_archerTemplate.m_damage[instance->m_levelArcher];
		switch (rand() % 2)
		{
		case 0:
			Mix_PlayChannel(-1, soundPool.find(ResID::Sound_ArrowFire_1)->second, 0);
			break;
		case 1:
			Mix_PlayChannel(-1, soundPool.find(ResID::Sound_ArrowFire_2)->second, 0);
			break;
		}
		break;
	case Axeman:
		interval = instance->m_axemanTemplate.m_interval[instance->m_levelAxeman];
		damage = instance->m_axemanTemplate.m_damage[instance->m_levelAxeman];
		Mix_PlayChannel(-1, soundPool.find(ResID::Sound_AxeFire)->second, 0);
		break;
	case Gunner:
		interval = instance->m_gunnerTemplate.m_interval[instance->m_levelGunner];
		damage = instance->m_gunnerTemplate.m_damage[instance->m_levelGunner];
		Mix_PlayChannel(-1, soundPool.find(ResID::Sound_ShellFire)->second, 0);
		break;
	}
	m_timerFire.setWaitTime(interval);
	m_timerFire.restart();

	TwoVector direction = targetEnemy->getPosition() - m_position;
	BulletManager::instance()->fireBullet(m_bulletType, m_position, direction.normalize() * m_fireSpeed * SIZE_TILE, damage);

	bool isShowXAnim = abs(direction.m_x) >= abs(direction.m_y);
	if (isShowXAnim)
	{
		m_facing = direction.m_x > 0 ? Facing::Right : Facing::Left;
	}
	else
	{
		m_facing = direction.m_y > 0 ? Facing::Down : Facing::Up;
	}

	updateFireAnimation();
	m_animCurrent->reset();
}