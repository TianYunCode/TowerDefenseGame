#pragma once

#include "Enemy.h"
#include "Manager.h"
#include "ConfigManager.h"
#include "HomeManager.h"
#include "SlimEnemy.h"
#include "KingSlimEnemy.h"
#include "SkeletonEnemy.h"
#include "GoblinEnemy.h"
#include "GoblinPriestEnemy.h"
#include "BulletManager.h"
#include "CoinManager.h"

#include <vector>
#include <SDL.h>

class EnemyManager : public Manager<EnemyManager>
{
	friend class Manager<EnemyManager>;

public:
	typedef std::vector<Enemy*> EnemyList;

public:
	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

	void spawnEnemy(EnemyType type, int idxSpawnPoint);
	bool checkCleared();

	EnemyManager::EnemyList& getEnemyList();

protected:
	EnemyManager() = default;
	~EnemyManager();

private:
	EnemyList m_enemyList;

private:
	void processHomeCollision();
	void processBulletCollision();
	void removeInvalidEnemy();
	void trySpawnCoinProp(const TwoVector& position, double ratio);
};
