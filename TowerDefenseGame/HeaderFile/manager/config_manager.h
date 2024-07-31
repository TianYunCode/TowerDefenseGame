#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include "../map.h"
#include "../wave.h"
#include "manager.h"

#include <SDL.h>
#include <string>
#include <cJSON.h>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class ConfigManager : public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

public:
	//基础模板
	struct BasicTemplate
	{
		string window_title = u8"村庄保卫战！"; //窗口标题
		int window_width = 1280;			   //窗口宽度
		int window_height = 720;			   //窗口高度
	};

	//玩家模板 具体从配置文件读取
	struct PlayerTemplate
	{
		double speed = 3;					 //速度，每秒移动3个单位
		double normal_attack_interval = 0.5; //普通攻击时间间隔，每0.5秒进行一次普通攻击
		double normal_attack_damage = 0;	 //普通攻击伤害
		double skill_interval = 10;			 //技能冷却时间，单位：秒
		double skill_damage = 1;			 //技能伤害
	};

	//防御塔模板 具体从配置文件读取
	struct TowerTemplate
	{
		double interval[10] = { 1 };	 //攻击时间间隔，每1秒攻击一次
		double damage[10] = { 25 };		 //攻击伤害
		double view_range[10] = { 5 };	 //视野范围，直径为5的圆
		double cost[10] = { 50 };		 //建造防御塔的费用
		double upgrade_cost[9] = { 75 }; //等级升级费用
	};

	//敌人模板 具体从配置文件读取
	struct EnemyTemplate
	{
		double hp = 100;			   //生命值
		double speed = 1;			   //移动速度，每秒移动1个单位
		double damage = 1;			   //伤害，进入基地后扣除一颗心
		double reward_ratio = 0.5;	   //金币爆率，0.5 = 50%概率
		double recover_interval = 10;  //回复技能时间间隔，每隔10秒会释放一次回复技能
		double recover_range = 0;	   //回复技能的范围，-1表示没有回复技能，0表示只回复自己，1以上表示以自身为中心的直径圆范围
		double recover_intensity = 25; //回复技能强度，表示回复25点血量
	};

public:
	Map map;
	vector<Wave> wave_list; //波次列表

	int level_archer = 0; //弓箭手等级
	int level_axeman = 0; //斧头兵等级
	int level_gunner = 0; //枪炮手等级

	bool is_game_win = true;        //游戏是否胜利
	bool is_game_over = false;	    //游戏是否结束
	SDL_Rect rect_tile_map = { 0 };

	BasicTemplate basic_template; //基础模板

	PlayerTemplate player_template; //玩家模板

	//防御塔模板
	TowerTemplate archer_template; //弓箭手
	TowerTemplate axeman_template; //斧头兵
	TowerTemplate gunner_template; //枪炮手

	//敌人模板
	EnemyTemplate slim_template;		  //史莱姆
	EnemyTemplate king_slim_template;	  //皇家史莱姆
	EnemyTemplate skeleton_template;	  //骷髅兵
	EnemyTemplate goblin_template;		  //哥布林
	EnemyTemplate goblin_priest_template; //哥布林祭司

	const double num_initial_hp = 10;	 //房屋生命值，10颗心
	const double num_initial_coin = 100; //初始金币数
	const double num_coin_per_prop = 10; //每个道具的硬币

public:
	bool load_level_config(const string& path);
	bool load_game_config(const string& path);

protected:
	ConfigManager() = default;
	~ConfigManager() = default;

private:
	void parse_basic_template(BasicTemplate& tpl, cJSON* json_root);
	void parse_player_template(PlayerTemplate& tpl, cJSON* json_root);
	void parse_number_array(double* ary, int max_len, cJSON* json_root);
	void parse_tower_template(TowerTemplate& tpl, cJSON* json_root);
	void parse_enemy_template(EnemyTemplate& tpl, cJSON* json_root);
};

#endif