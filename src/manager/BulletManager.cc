#include "BulletManager.h"

BulletManager::~BulletManager()
{
	for (Bullet* bullet : m_bulletList)
	{
		delete bullet;
		bullet = nullptr;
	}
}

void BulletManager::onUpdate(double delta)
{
	for (Bullet* bullet : m_bulletList)
	{
		bullet->onUpdate(delta);
	}

	m_bulletList.erase(std::remove_if(m_bulletList.begin(), m_bulletList.end(), [](const Bullet* bullet)
		{
			bool deletable = bullet->canRemove();

			if (deletable)
			{
				delete bullet;
				bullet = nullptr;
			}

			return deletable;
		}), m_bulletList.end());
}

void BulletManager::onRender(SDL_Renderer* renderer)
{
	for (Bullet* bullet : m_bulletList)
	{
		bullet->onRender(renderer);
	}
}

BulletManager::BulletList& BulletManager::getBulletList()
{
	return m_bulletList;
}

void BulletManager::fireBullet(BulletType type, const TwoVector& position, const TwoVector& velocity, double damage)
{
	Bullet* bullet = nullptr;

	switch (type)
	{
	case Arrow:
		bullet = new ArrowBullet();
		break;
	case Axe:
		bullet = new AxeBullet();
		break;
	case Shell:
		bullet = new ShellBullet();
		break;
	default:
		bullet = new ArrowBullet();
		break;
	}

	bullet->setPosition(position);
	bullet->setVelocity(velocity);
	bullet->setDamage(damage);

	m_bulletList.push_back(bullet);
}