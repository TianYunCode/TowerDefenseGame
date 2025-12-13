#pragma once

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart();

	void setWaitTime(double val);
	void setOneShot(bool flag);
	void setOnTimeout(std::function<void()> onTimeout);

	void pause();
	void resume();

	void onUpdate(double delta);

private:
	double m_passTime = 0;
	double m_waitTime = 0;
	bool m_paused = false;
	bool m_shotted = false;
	bool m_oneShot = false;
	std::function<void()> m_onTimeout;
};
