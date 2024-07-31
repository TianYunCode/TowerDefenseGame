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
	//����ģ��
	struct BasicTemplate
	{
		string window_title = u8"��ׯ����ս��"; //���ڱ���
		int window_width = 1280;			   //���ڿ��
		int window_height = 720;			   //���ڸ߶�
	};

	//���ģ�� ����������ļ���ȡ
	struct PlayerTemplate
	{
		double speed = 3;					 //�ٶȣ�ÿ���ƶ�3����λ
		double normal_attack_interval = 0.5; //��ͨ����ʱ������ÿ0.5�����һ����ͨ����
		double normal_attack_damage = 0;	 //��ͨ�����˺�
		double skill_interval = 10;			 //������ȴʱ�䣬��λ����
		double skill_damage = 1;			 //�����˺�
	};

	//������ģ�� ����������ļ���ȡ
	struct TowerTemplate
	{
		double interval[10] = { 1 };	 //����ʱ������ÿ1�빥��һ��
		double damage[10] = { 25 };		 //�����˺�
		double view_range[10] = { 5 };	 //��Ұ��Χ��ֱ��Ϊ5��Բ
		double cost[10] = { 50 };		 //����������ķ���
		double upgrade_cost[9] = { 75 }; //�ȼ���������
	};

	//����ģ�� ����������ļ���ȡ
	struct EnemyTemplate
	{
		double hp = 100;			   //����ֵ
		double speed = 1;			   //�ƶ��ٶȣ�ÿ���ƶ�1����λ
		double damage = 1;			   //�˺���������غ�۳�һ����
		double reward_ratio = 0.5;	   //��ұ��ʣ�0.5 = 50%����
		double recover_interval = 10;  //�ظ�����ʱ������ÿ��10����ͷ�һ�λظ�����
		double recover_range = 0;	   //�ظ����ܵķ�Χ��-1��ʾû�лظ����ܣ�0��ʾֻ�ظ��Լ���1���ϱ�ʾ������Ϊ���ĵ�ֱ��Բ��Χ
		double recover_intensity = 25; //�ظ�����ǿ�ȣ���ʾ�ظ�25��Ѫ��
	};

public:
	Map map;
	vector<Wave> wave_list; //�����б�

	int level_archer = 0; //�����ֵȼ�
	int level_axeman = 0; //��ͷ���ȼ�
	int level_gunner = 0; //ǹ���ֵȼ�

	bool is_game_win = true;        //��Ϸ�Ƿ�ʤ��
	bool is_game_over = false;	    //��Ϸ�Ƿ����
	SDL_Rect rect_tile_map = { 0 };

	BasicTemplate basic_template; //����ģ��

	PlayerTemplate player_template; //���ģ��

	//������ģ��
	TowerTemplate archer_template; //������
	TowerTemplate axeman_template; //��ͷ��
	TowerTemplate gunner_template; //ǹ����

	//����ģ��
	EnemyTemplate slim_template;		  //ʷ��ķ
	EnemyTemplate king_slim_template;	  //�ʼ�ʷ��ķ
	EnemyTemplate skeleton_template;	  //���ñ�
	EnemyTemplate goblin_template;		  //�粼��
	EnemyTemplate goblin_priest_template; //�粼�ּ�˾

	const double num_initial_hp = 10;	 //��������ֵ��10����
	const double num_initial_coin = 100; //��ʼ�����
	const double num_coin_per_prop = 10; //ÿ�����ߵ�Ӳ��

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