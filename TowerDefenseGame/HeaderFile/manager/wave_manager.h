#ifndef _WAVE_MANAGER_H_
#define _WAVE_MANAGER_H_

#include "timer.h"
#include "manager.h"
#include "config_manager.h"
#include "enemy_manager.h"
#include "coin_manager.h"

class WaveManager : public Manager<WaveManager>
{
	friend class Manager<WaveManager>;

public:
	void on_update(double delta);

protected:
	WaveManager();
	~WaveManager() = default;

private:
	int idx_wave = 0;
	int idx_spawn_event = 0;
	Timer timer_start_wave;
	Timer timer_spawn_enemy;
	bool is_wave_started = false;
	bool is_spawned_last_enemy = false;
};

#endif