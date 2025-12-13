#include "HomeManager.h"

HomeManager::HomeManager()
{
	m_numHp = ConfigManager::instance()->m_numInitialHp;
}

double HomeManager::getCurrentHpNum()
{
	return m_numHp;
}

void HomeManager::decreaseHp(double val)
{
	m_numHp -= val;

	if (m_numHp < 0)
	{
		m_numHp = 0;
	}

	static const ResourcesManager::SoundPool& sound_pool = ResourcesManager::instance()->getSoundPool();

	Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_HomeHurt)->second, 0);
}