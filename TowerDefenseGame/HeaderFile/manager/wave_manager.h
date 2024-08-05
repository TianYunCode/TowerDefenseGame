#ifndef _WAVE_MANAGER_H_
#define _WAVE_MANAGER_H_

#include "timer.h"
#include "manager.h"
#include "config_manager.h"
#include "enemy_manager.h"
#include "coin_manager.h"

//���ι�����
class WaveManager : public Manager<WaveManager>
{
	friend class Manager<WaveManager>;

public:
	void on_update(double delta);

protected:
	WaveManager();
	~WaveManager() = default;

private:
	int idx_wave = 0;					//�ڼ�����
	int idx_spawn_event = 0;			//�ڼ����ε������¼�
	Timer timer_start_wave;				//���ο�ʼǰ��ʱ�䣨��Ϸ��ʼ�󣬼����Ӻ�ų��ֵ��ˣ�
	Timer timer_spawn_enemy;			//�����¼���ʱ����
	bool is_wave_started = false;		//�Ƿ��Ѿ����ɵ���
	bool is_spawned_last_enemy = false; //�Ƿ��Ѿ��������һ������
};

#endif