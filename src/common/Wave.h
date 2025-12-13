#pragma once

#include "EnemyType.h"

#include <vector>

struct Wave
{
	struct SpawnEvent
	{
		double m_interval = 0;
		int m_spawnPoint = 1;
		EnemyType m_enemyType = EnemyType::Slim;
	};

	double m_rawards = 0;
	double m_interval = 0;
	std::vector<SpawnEvent> m_spawnEventList;
};
