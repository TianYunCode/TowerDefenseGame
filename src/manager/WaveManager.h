#pragma once

#include "Timer.h"
#include "Manager.h"
#include "ConfigManager.h"
#include "EnemyManager.h"
#include "CoinManager.h"

class WaveManager : public Manager<WaveManager>
{
	friend class Manager<WaveManager>;

public:
	void onUpdate(double delta);

protected:
	WaveManager();
	~WaveManager() = default;

private:
	int m_idxWave = 0;
	int m_idxSpawnEvent = 0;
	Timer m_timerStartWave;
	Timer m_timerSpawnEnemy;
	bool m_isWaveStarted = false;
	bool m_isSpawnedLastEnemy = false;
};
