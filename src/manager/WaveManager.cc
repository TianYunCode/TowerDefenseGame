#include "WaveManager.h"

WaveManager::WaveManager()
{
	static const std::vector<Wave>& waveList = ConfigManager::instance()->m_waveList;

	m_timerStartWave.setOneShot(true);
	m_timerStartWave.setWaitTime(waveList[0].m_interval);
	m_timerStartWave.setOnTimeout([&]()
		{
			m_isWaveStarted = true;
			m_timerSpawnEnemy.setWaitTime(waveList[m_idxWave].m_spawnEventList[0].m_interval);
			m_timerSpawnEnemy.restart();
		}
	);

	m_timerSpawnEnemy.setOneShot(true);
	m_timerSpawnEnemy.setOnTimeout([&]()
		{
			const std::vector<Wave::SpawnEvent>& spawnEventList = waveList[m_idxWave].m_spawnEventList;
			const Wave::SpawnEvent& spawnEvent = spawnEventList[m_idxSpawnEvent];

			EnemyManager::instance()->spawnEnemy(spawnEvent.m_enemyType, spawnEvent.m_spawnPoint);

			m_idxSpawnEvent++;

			if (m_idxSpawnEvent >= spawnEventList.size())
			{
				m_isSpawnedLastEnemy = true;
				return;
			}

			m_timerSpawnEnemy.setWaitTime(spawnEventList[m_idxSpawnEvent].m_interval);
			m_timerSpawnEnemy.restart();
		}
	);
}

void WaveManager::onUpdate(double delta)
{
	static ConfigManager* instance = ConfigManager::instance();

	if (instance->m_isGameOver)
	{
		return;
	}

	if (!m_isWaveStarted)
	{
		m_timerStartWave.onUpdate(delta);
	}
	else
	{
		m_timerSpawnEnemy.onUpdate(delta);
	}

	if (m_isSpawnedLastEnemy && EnemyManager::instance()->checkCleared())
	{
		CoinManager::instance()->increaseCoin(instance->m_waveList[m_idxWave].m_rawards);

		m_idxWave++;

		if (m_idxWave >= instance->m_waveList.size())
		{
			instance->m_isGameWin = true;
			instance->m_isGameOver = true;
		}
		else
		{
			m_idxSpawnEvent = 0;
			m_isWaveStarted = true;
			m_isSpawnedLastEnemy = false;

			const Wave& wave = instance->m_waveList[m_idxWave];
			m_timerStartWave.setWaitTime(wave.m_interval);
			m_timerStartWave.restart();
		}
	}
}