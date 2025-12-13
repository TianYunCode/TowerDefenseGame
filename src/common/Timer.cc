#include "Timer.h"

void Timer::restart()
{
	m_passTime = 0;
	m_shotted = false;
}

void Timer::setWaitTime(double val)
{
	m_waitTime = val;
}

void Timer::setOneShot(bool flag)
{
	m_oneShot = false;
}

void Timer::setOnTimeout(std::function<void()> onTimeout)
{
	this->m_onTimeout = onTimeout;
}

void Timer::pause()
{
	m_paused = true;
}

void Timer::resume()
{
	m_paused = false;
}

void Timer::onUpdate(double delta)
{
	if (m_paused)
	{
		return;
	}

	m_passTime += delta;
	if (m_passTime >= m_waitTime)
	{
		bool canShot = (!m_oneShot || (m_oneShot && !m_shotted));
		m_shotted = true;
		if (canShot && m_onTimeout)
		{
			m_onTimeout();
		}

		m_passTime -= m_waitTime;
	}
}