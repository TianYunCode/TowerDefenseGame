#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

using namespace std;

//��ʱ����
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart(); //���ö�ʱ��״̬

	void set_wait_time(double val);					  //���õȴ�ʱ��
	void set_one_shot(bool flag);					  //���ô���״̬
	void set_on_timeout(function<void()> on_timeout); //���ûص�����

	void pause();  //��ͣ
	void resume(); //�ָ�

	void on_update(double delta); //����

private:
	double pass_time = 0;		 //��ȥ��ʱ��
	double wait_time = 0;		 //�ȴ���ʱ��
	bool paused = false;		 //��ͣ
	bool shotted = false;		 //�Ƿ񴥷���
	bool one_shot = false;		 //�Ƿ���Ҫ���δ���
	function<void()> on_timeout; //�ص�����
};

#endif