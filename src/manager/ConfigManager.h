#pragma once

#include "Map.h"
#include "Wave.h"
#include "Manager.h"

#include <SDL.h>
#include <string>
#include <cJSON.h>
#include <fstream>
#include <sstream>
#include <iostream>

class ConfigManager : public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

public:
	// 基本模板
	struct BasicTemplate
	{
		std::string m_windowTitle = u8"村庄保卫战！";
		int m_windowWidth = 1280;
		int m_windowHeight = 720;
	};

	// 玩家模板
	struct PlayerTemplate
	{
		double m_speed = 3;
		double m_normalAttackInterval = 0.5;
		double m_normalAttackDamage = 0;
		double m_skillInterval = 10;
		double m_skillDamage = 1;
	};

	// 防御塔模板
	struct TowerTemplate
	{
		double m_interval[10] = { 1 };
		double m_damage[10] = { 25 };
		double m_viewRange[10] = { 5 };
		double m_cost[10] = { 50 };
		double m_upgradeCost[9] = { 75 };
	};

	// 敌人模板
	struct EnemyTemplate
	{
		double m_hp = 100;
		double m_speed = 1;
		double m_damage = 1;
		double m_rewardRatio = 0.5;
		double m_recoverInterval = 10;
		double m_recoverRange = 0;
		double m_recoverIntensity = 25;
	};

public:
	Map m_map;
	std::vector<Wave> m_waveList;

	int m_levelArcher = 0;
	int m_levelAxeman = 0;
	int m_levelGunner = 0;

	bool m_isGameWin = true;
	bool m_isGameOver = false;
	SDL_Rect m_rectTileMap = { 0 };

	BasicTemplate m_basicTemplate;

	PlayerTemplate m_playerTemplate;

	TowerTemplate m_archerTemplate;
	TowerTemplate m_axemanTemplate;
	TowerTemplate m_gunnerTemplate;

	EnemyTemplate m_slimTemplate;
	EnemyTemplate m_kingSlimTemplate;
	EnemyTemplate m_skeletonTemplate;
	EnemyTemplate m_goblinTemplate;
	EnemyTemplate m_goblinPriestTemplate;

	const double m_numInitialHp = 10;
	const double m_numInitialCoin = 100;
	const double m_numCoinPerProp = 10;

public:
	/**
	* 加载等级配置
	*/
	bool loadLevelConfig(const std::string& path);

	/**
	* 加载游戏配置
	*/
	bool loadGameConfig(const std::string& path);

protected:
	ConfigManager() = default;
	~ConfigManager() = default;

private:
	/**
	* 解析basic
	*/
	void parseBasicTemplate(BasicTemplate& tpl, cJSON* jsonRoot);

	/**
	* 解析player
	*/
	void parsePlayerTemplate(PlayerTemplate& tpl, cJSON* jsonRoot);

	/**
	* 解析纯数字数组字段
	*/
	void parseNumberArray(double* ary, int maxLen, cJSON* jsonRoot);

	/**
	* 解析tower
	*/
	void parseTowerTemplate(TowerTemplate& tpl, cJSON* jsonRoot);

	/**
	* 解析enemy
	*/
	void parseEnemyTemplate(EnemyTemplate& tpl, cJSON* jsonRoot);
};
