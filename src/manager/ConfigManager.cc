#include "ConfigManager.h"

bool ConfigManager::loadLevelConfig(const std::string& path)
{
	std::ifstream file(path);

	if (!file.good())
	{
		return false;
	}

	std::stringstream strStream;
	strStream << file.rdbuf(); file.close();

	cJSON* jsonRoot = cJSON_Parse(strStream.str().c_str());
	if (!jsonRoot)
	{
		return false;
	}

	if (jsonRoot->type != cJSON_Array)
	{
		cJSON_Delete(jsonRoot);
		return false;
	}

	cJSON* jsonWave = nullptr;
	cJSON_ArrayForEach(jsonWave, jsonRoot)
	{
		if (jsonWave->type != cJSON_Object)
		{
			continue;
		}

		m_waveList.emplace_back();
		Wave& wave = m_waveList.back();

		cJSON* jsonWaveRewards = cJSON_GetObjectItem(jsonWave, "rewards");
		if (jsonWaveRewards && jsonWaveRewards->type == cJSON_Number)
		{
			wave.m_rawards = jsonWaveRewards->valuedouble;
		}

		cJSON* jsonWaveInterval = cJSON_GetObjectItem(jsonWave, "interval");
		if (jsonWaveInterval && jsonWaveInterval->type == cJSON_Number)
		{
			wave.m_interval = jsonWaveInterval->valuedouble;
		}

		cJSON* jsonWaveSpawnList = cJSON_GetObjectItem(jsonWave, "spawn_list");
		if (jsonWaveSpawnList && jsonWaveSpawnList->type == cJSON_Array)
		{
			cJSON* jsonSpawnEvent = nullptr;
			cJSON_ArrayForEach(jsonSpawnEvent, jsonWaveSpawnList)
			{
				if (jsonSpawnEvent->type != cJSON_Object)
				{
					continue;
				}

				wave.m_spawnEventList.emplace_back();
				Wave::SpawnEvent& spawnEvent = wave.m_spawnEventList.back();

				cJSON* jsonSpawnEventInterval = cJSON_GetObjectItem(jsonSpawnEvent, "interval");
				if (jsonSpawnEventInterval && jsonSpawnEventInterval->type == cJSON_Number)
				{
					spawnEvent.m_interval = jsonSpawnEventInterval->valuedouble;
				}

				cJSON* jsonSpawnEventSpawnPoint = cJSON_GetObjectItem(jsonSpawnEvent, "point");
				if (jsonSpawnEventSpawnPoint && jsonSpawnEventSpawnPoint->type == cJSON_Number)
				{
					spawnEvent.m_spawnPoint = jsonSpawnEventSpawnPoint->valueint;
				}

				cJSON* jsonSpawnEventEnemyType = cJSON_GetObjectItem(jsonSpawnEvent, "enemy");
				if (jsonSpawnEventEnemyType && jsonSpawnEventEnemyType->type == cJSON_String)
				{
					const std::string strEnemyType = jsonSpawnEventEnemyType->valuestring;
					if (strEnemyType == "Slim")
					{
						spawnEvent.m_enemyType = EnemyType::Slim;
					}
					else if (strEnemyType == "KingSlim")
					{
						spawnEvent.m_enemyType = EnemyType::KingSlim;
					}
					else if (strEnemyType == "Skeleton")
					{
						spawnEvent.m_enemyType = EnemyType::Skeleton;
					}
					else if (strEnemyType == "Goblin")
					{
						spawnEvent.m_enemyType = EnemyType::Goblin;
					}
					else if (strEnemyType == "GoblinPriest")
					{
						spawnEvent.m_enemyType = EnemyType::GoblinPriest;
					}
				}
			}

			if (wave.m_spawnEventList.empty())
			{
				m_waveList.pop_back();
			}
		}
	}

	cJSON_Delete(jsonRoot);

	if (m_waveList.empty())
	{
		return false;
	}

	return true;
}

bool ConfigManager::loadGameConfig(const std::string& path)
{
	std::ifstream file(path);
	if (!file.good())
	{
		return false;
	}

	std::stringstream strStream;
	strStream << file.rdbuf(); file.close();

	cJSON* jsonRoot = cJSON_Parse(strStream.str().c_str());
	if (!jsonRoot || jsonRoot->type != cJSON_Object)
	{
		return false;
	}

	cJSON* jsonBasic = cJSON_GetObjectItem(jsonRoot, "basic");
	cJSON* jsonPlayer = cJSON_GetObjectItem(jsonRoot, "player");
	cJSON* jsonTower = cJSON_GetObjectItem(jsonRoot, "tower");
	cJSON* jsonEnemy = cJSON_GetObjectItem(jsonRoot, "enemy");

	if (!jsonBasic || !jsonPlayer || !jsonTower || !jsonEnemy
		|| jsonBasic->type != cJSON_Object || jsonPlayer->type != cJSON_Object
		|| jsonTower->type != cJSON_Object || jsonEnemy->type != cJSON_Object)
	{
		cJSON_Delete(jsonRoot);
		return false;
	}

	parseBasicTemplate(m_basicTemplate, jsonBasic);

	parsePlayerTemplate(m_playerTemplate, jsonPlayer);

	parseTowerTemplate(m_archerTemplate, cJSON_GetObjectItem(jsonTower, "archer"));
	parseTowerTemplate(m_axemanTemplate, cJSON_GetObjectItem(jsonTower, "axeman"));
	parseTowerTemplate(m_gunnerTemplate, cJSON_GetObjectItem(jsonTower, "gunner"));

	parseEnemyTemplate(m_slimTemplate, cJSON_GetObjectItem(jsonEnemy, "slim"));
	parseEnemyTemplate(m_kingSlimTemplate, cJSON_GetObjectItem(jsonEnemy, "king_slim"));
	parseEnemyTemplate(m_skeletonTemplate, cJSON_GetObjectItem(jsonEnemy, "skeleton"));
	parseEnemyTemplate(m_goblinTemplate, cJSON_GetObjectItem(jsonEnemy, "goblin"));
	parseEnemyTemplate(m_goblinPriestTemplate, cJSON_GetObjectItem(jsonEnemy, "goblin_priest"));

	cJSON_Delete(jsonRoot);
	return true;
}

void ConfigManager::parseBasicTemplate(BasicTemplate& tpl, cJSON* jsonRoot)
{
	if (!jsonRoot || jsonRoot->type != cJSON_Object)
	{
		return;
	}

	cJSON* jsonWindowTitle = cJSON_GetObjectItem(jsonRoot, "window_title");
	cJSON* jsonWindowWidth = cJSON_GetObjectItem(jsonRoot, "window_width");
	cJSON* jsonWindowHeight = cJSON_GetObjectItem(jsonRoot, "window_height");

	if (jsonWindowTitle && jsonWindowTitle->type == cJSON_String)
	{
		tpl.m_windowTitle = jsonWindowTitle->valuestring;
	}

	if (jsonWindowWidth && jsonWindowWidth->type == cJSON_Number)
	{
		tpl.m_windowWidth = jsonWindowWidth->valueint;
	}

	if (jsonWindowHeight && jsonWindowHeight->type == cJSON_Number)
	{
		tpl.m_windowHeight = jsonWindowHeight->valueint;
	}
}

void ConfigManager::parsePlayerTemplate(PlayerTemplate& tpl, cJSON* jsonRoot)
{
	if (!jsonRoot || jsonRoot->type != cJSON_Object)
	{
		return;
	}

	cJSON* jsonSpeed = cJSON_GetObjectItem(jsonRoot, "speed");
	cJSON* jsonNormalAttackInterval = cJSON_GetObjectItem(jsonRoot, "normal_attack_interval");
	cJSON* jsonNormalAttackDamage = cJSON_GetObjectItem(jsonRoot, "normal_attack_damage");
	cJSON* jsonSkillInterval = cJSON_GetObjectItem(jsonRoot, "skill_interval");
	cJSON* jsonSkillDamage = cJSON_GetObjectItem(jsonRoot, "skill_damage");

	if (jsonSpeed && jsonSpeed->type == cJSON_Number)
	{
		tpl.m_speed = jsonSpeed->valuedouble;
	}

	if (jsonNormalAttackInterval && jsonNormalAttackInterval->type == cJSON_Number)
	{
		tpl.m_normalAttackInterval = jsonNormalAttackInterval->valuedouble;
	}

	if (jsonNormalAttackDamage && jsonNormalAttackDamage->type == cJSON_Number)
	{
		tpl.m_normalAttackDamage = jsonNormalAttackDamage->valuedouble;
	}

	if (jsonSkillInterval && jsonSkillInterval->type == cJSON_Number)
	{
		tpl.m_skillInterval = jsonSkillInterval->valuedouble;
	}

	if (jsonSkillDamage && jsonSkillDamage->type == cJSON_Number)
	{
		tpl.m_skillDamage = jsonSkillDamage->valuedouble;
	}
}

void ConfigManager::parseNumberArray(double* ary, int maxLen, cJSON* jsonRoot)
{
	if (!jsonRoot || jsonRoot->type != cJSON_Array)
	{
		return;
	}

	int idx = -1;
	cJSON* jsonElement = nullptr;
	cJSON_ArrayForEach(jsonElement, jsonRoot)
	{
		idx++;
		if (jsonElement->type != cJSON_Number || idx >= maxLen)
		{
			continue;
		}

		ary[idx] = jsonElement->valuedouble;
	}
}

void ConfigManager::parseTowerTemplate(TowerTemplate& tpl, cJSON* jsonRoot)
{
	if (!jsonRoot || jsonRoot->type != cJSON_Object)
	{
		return;
	}

	cJSON* jsonInterval = cJSON_GetObjectItem(jsonRoot, "interval");
	cJSON* jsonDamage = cJSON_GetObjectItem(jsonRoot, "damage");
	cJSON* jsonViewRange = cJSON_GetObjectItem(jsonRoot, "view_range");
	cJSON* jsonCost = cJSON_GetObjectItem(jsonRoot, "cost");
	cJSON* jsonUpgradeCost = cJSON_GetObjectItem(jsonRoot, "upgrade_cost");

	parseNumberArray(tpl.m_interval, 10, jsonInterval);
	parseNumberArray(tpl.m_damage, 10, jsonDamage);
	parseNumberArray(tpl.m_viewRange, 10, jsonViewRange);
	parseNumberArray(tpl.m_cost, 10, jsonCost);
	parseNumberArray(tpl.m_upgradeCost, 9, jsonUpgradeCost);
}

void ConfigManager::parseEnemyTemplate(EnemyTemplate& tpl, cJSON* jsonRoot)
{
	if (!jsonRoot || jsonRoot->type != cJSON_Object)
	{
		return;
	}

	cJSON* jsonHp = cJSON_GetObjectItem(jsonRoot, "hp");
	cJSON* jsonSpeed = cJSON_GetObjectItem(jsonRoot, "speed");
	cJSON* jsonDamage = cJSON_GetObjectItem(jsonRoot, "damage");
	cJSON* jsonRewardRatio = cJSON_GetObjectItem(jsonRoot, "reward_ratio");
	cJSON* jsonRecoverInterval = cJSON_GetObjectItem(jsonRoot, "recover_interval");
	cJSON* jsonRecoverRange = cJSON_GetObjectItem(jsonRoot, "recover_range");
	cJSON* jsonRecoverIntensity = cJSON_GetObjectItem(jsonRoot, "recover_intensity");

	if (jsonHp && jsonHp->type == cJSON_Number)
	{
		tpl.m_hp = jsonHp->valuedouble;
	}

	if (jsonSpeed && jsonSpeed->type == cJSON_Number)
	{
		tpl.m_speed = jsonSpeed->valuedouble;
	}

	if (jsonDamage && jsonDamage->type == cJSON_Number)
	{
		tpl.m_damage = jsonDamage->valuedouble;
	}

	if (jsonRewardRatio && jsonRewardRatio->type == cJSON_Number)
	{
		tpl.m_rewardRatio = jsonRewardRatio->valuedouble;
	}

	if (jsonRecoverInterval && jsonRecoverInterval->type == cJSON_Number)
	{
		tpl.m_recoverInterval = jsonRecoverInterval->valuedouble;
	}

	if (jsonRecoverRange && jsonRecoverRange->type == cJSON_Number)
	{
		tpl.m_recoverRange = jsonRecoverRange->valuedouble;
	}

	if (jsonRecoverIntensity && jsonRecoverIntensity->type == cJSON_Number)
	{
		tpl.m_recoverIntensity = jsonRecoverIntensity->valuedouble;
	}
}
