#ifndef _WAVE_MANAGER_H_
#define _WAVE_MANAGER_H_

#include "timer.h"
#include "manager.h"
#include "config_manager.h"
#include "enemy_manager.h"
#include "coin_manager.h"

//波次管理类
class WaveManager : public Manager<WaveManager>
{
	friend class Manager<WaveManager>;

public:
	void on_update(double delta);

protected:
	WaveManager();
	~WaveManager() = default;

private:
	int idx_wave = 0;					//第几波次
	int idx_spawn_event = 0;			//第几波次的生成事件
	Timer timer_start_wave;				//波次开始前的时间（游戏开始后，几秒钟后才出现敌人）
	Timer timer_spawn_enemy;			//生成事件的时间间隔
	bool is_wave_started = false;		//是否已经生成敌人
	bool is_spawned_last_enemy = false; //是否已经生成最后一个敌人
};

#endif