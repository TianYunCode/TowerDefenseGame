#include "EnemyManager.h"

EnemyManager::~EnemyManager()
{
	for (Enemy* enemy : m_enemyList)
	{
		delete enemy;
	}
}

void EnemyManager::onUpdate(double delta)
{
	for (Enemy* enemy : m_enemyList)
	{
		enemy->onUpdate(delta);
	}

	processHomeCollision();
	processBulletCollision();

	removeInvalidEnemy();
}

void EnemyManager::onRender(SDL_Renderer* renderer)
{
	for (Enemy* enemy : m_enemyList)
	{
		enemy->onRender(renderer);
	}
}

void EnemyManager::spawnEnemy(EnemyType type, int idxSpawnPoint)
{
	static TwoVector position;
	static const SDL_Rect& rectTileMap = ConfigManager::instance()->m_rectTileMap;
	static const Map::SpawnerRoutePool& spawnerRoutePool = ConfigManager::instance()->m_map.getIdxSpawnerPool();

	const auto& itor = spawnerRoutePool.find(idxSpawnPoint);
	if (itor == spawnerRoutePool.end())
	{
		return;
	}

	Enemy* enemy = nullptr;

	switch (type)
	{
	case EnemyType::Slim:
		enemy = new SlimEnemy();
		break;
	case EnemyType::KingSlim:
		enemy = new KingSlimeEnemy();
		break;
	case EnemyType::Skeleton:
		enemy = new SkeletonEnemy();
		break;
	case EnemyType::Goblin:
		enemy = new GoblinEnemy();
		break;
	case EnemyType::GoblinPriest:
		enemy = new GoblinPriestEnemy();
		break;
	default:
		enemy = new SlimEnemy();
		break;
	}

	enemy->setOnSkillReleased([&](Enemy* enemySrc)
		{
			double recoverRaduis = enemySrc->getRecoverRadius();
			if (recoverRaduis < 0)
			{
				return;
			}

			const TwoVector posSrc = enemySrc->getPosition();
			for (Enemy* enemyDst : m_enemyList)
			{
				const TwoVector& posDst = enemyDst->getPosition();
				double distance = (posDst - posSrc).length();
				if (distance <= recoverRaduis)
				{
					enemyDst->increaseHp(enemySrc->getRecoverIntensity());
				}
			}
		});

	const Route::IdxList& idxList = itor->second.getIdxList();
	position.m_x = rectTileMap.x + idxList[0].x * SIZE_TILE + SIZE_TILE / 2;
	position.m_y = rectTileMap.y + idxList[0].y * SIZE_TILE + SIZE_TILE / 2;

	enemy->setPosition(position);
	enemy->setRoute(&itor->second);

	m_enemyList.push_back(enemy);
}

bool EnemyManager::checkCleared()
{
	return m_enemyList.empty();
}

EnemyManager::EnemyList& EnemyManager::getEnemyList()
{
	return m_enemyList;
}

void EnemyManager::processHomeCollision()
{
	static const SDL_Point& idxHome = ConfigManager::instance()->m_map.getIdxHome();
	static const SDL_Rect& rectTileMap = ConfigManager::instance()->m_rectTileMap;
	static const TwoVector positionHomeTile =
	{
		(double)rectTileMap.x + idxHome.x * SIZE_TILE,
		(double)rectTileMap.y + idxHome.y * SIZE_TILE
	};

	for (Enemy* enemy : m_enemyList)
	{
		if (enemy->canRemove())
		{
			continue;
		}

		const TwoVector& position = enemy->getPosition();

		if (position.m_x >= positionHomeTile.m_x
			&& position.m_y >= positionHomeTile.m_y
			&& position.m_x <= positionHomeTile.m_x + SIZE_TILE
			&& position.m_y <= positionHomeTile.m_y + SIZE_TILE)
		{
			enemy->makeInvalid();

			HomeManager::instance()->decreaseHp(enemy->getDamage());
		}
	}
}

void EnemyManager::processBulletCollision()
{
	static BulletManager::BulletList& bulletList = BulletManager::instance()->getBulletList();

	for (Enemy* enemy : m_enemyList)
	{
		if (enemy->canRemove())
		{
			continue;
		}

		const TwoVector& sizeEnemy = enemy->getSize();
		const TwoVector& posEnemy = enemy->getPosition();

		for (Bullet* bullet : bulletList)
		{
			if (!bullet->canCollide())
			{
				continue;
			}

			const TwoVector& posBullet = bullet->getPosition();

			if (posBullet.m_x >= posEnemy.m_x - sizeEnemy.m_x / 2
				&& posBullet.m_y >= posEnemy.m_y - sizeEnemy.m_y / 2
				&& posBullet.m_x <= posEnemy.m_x + sizeEnemy.m_x / 2
				&& posBullet.m_y <= posEnemy.m_y + sizeEnemy.m_y / 2)
			{
				double damage = bullet->getDamage();
				double damageRange = bullet->getDamageRange();
				if (damageRange < 0)
				{
					enemy->decreaseHp(damage);
					if (enemy->canRemove())
					{
						trySpawnCoinProp(posEnemy, enemy->getRewardRatio());
					}
				}
				else
				{
					for (Enemy* targetEnemy : m_enemyList)
					{
						const TwoVector& posTargetEnemy = targetEnemy->getPosition();
						if ((posTargetEnemy - posBullet).length() <= damageRange)
						{
							targetEnemy->decreaseHp(damage);
							if (targetEnemy->canRemove())
							{
								trySpawnCoinProp(posTargetEnemy, enemy->getRewardRatio());
							}
						}
					}
				}

				bullet->onCollide(enemy);
			}
		}
	}
}

void EnemyManager::removeInvalidEnemy()
{
	m_enemyList.erase(std::remove_if(m_enemyList.begin(), m_enemyList.end(), [](const Enemy* enemy)
		{
			bool deletable = enemy->canRemove();

			if (deletable)
			{
				delete enemy;
				enemy = nullptr;
			}

			return deletable;
		}), m_enemyList.end());
}

void EnemyManager::trySpawnCoinProp(const TwoVector& position, double ratio)
{
	static CoinManager* instance = CoinManager::instance();

	if ((double)(rand() % 100) / 100 <= ratio)
	{
		instance->spawnCoinProp(position);
	}
}