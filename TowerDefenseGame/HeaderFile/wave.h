#ifndef _WAVE_H_
#define _WAVE_H_

#include "enemy_type.h"

#include <vector>

//波次结构体
struct Wave
{
	//波次信息 具体从配置文件读取
	struct SpawnEvent
	{
		double interval = 0;				    //敌人刷新时间间隔
		int spawn_point = 1;				    //敌人出生点
		EnemyType enemy_type = EnemyType::Slim; //生成的敌人
	};

	double rawards = 0;					 //波次开始前获得金币数量
	double interval = 0;				 //上一波次结束后，经过interval秒后本波次开始
	vector<SpawnEvent> spawn_event_list; //本波次的敌人列表
};

#endif