#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

using namespace std;

//定时器类
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart(); //重置定时器状态

	void set_wait_time(double val);					  //设置等待时间
	void set_one_shot(bool flag);					  //设置触发状态
	void set_on_timeout(function<void()> on_timeout); //设置回调函数

	void pause();  //暂停
	void resume(); //恢复

	void on_update(double delta); //更新

private:
	double pass_time = 0;		 //过去的时间
	double wait_time = 0;		 //等待的时间
	bool paused = false;		 //暂停
	bool shotted = false;		 //是否触发了
	bool one_shot = false;		 //是否需要单次触发
	function<void()> on_timeout; //回调函数
};

#endif