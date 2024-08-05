#ifndef _WAVE_H_
#define _WAVE_H_

#include "enemy_type.h"

#include <vector>

//���νṹ��
struct Wave
{
	//������Ϣ ����������ļ���ȡ
	struct SpawnEvent
	{
		double interval = 0;				    //����ˢ��ʱ����
		int spawn_point = 1;				    //���˳�����
		EnemyType enemy_type = EnemyType::Slim; //���ɵĵ���
	};

	double rawards = 0;					 //���ο�ʼǰ��ý������
	double interval = 0;				 //��һ���ν����󣬾���interval��󱾲��ο�ʼ
	vector<SpawnEvent> spawn_event_list; //�����εĵ����б�
};

#endif