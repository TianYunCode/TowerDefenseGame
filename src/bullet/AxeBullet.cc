#include "AxeBullet.h"

AxeBullet::AxeBullet()
{
	static SDL_Texture* texAxe = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_BulletAxe)->second;

	static const std::vector<int> idxList = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	m_animation.setLoop(true);
	m_animation.setInterval(0.1);
	m_animation.setFrameData(texAxe, 4, 2, idxList);

	m_size.m_x = 48, m_size.m_y = 48;
}

void AxeBullet::onCollide(Enemy* enemy)
{
	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	switch (rand() % 3)
	{
	case 0:
		Mix_PlayChannel(-1, soundPool.find(ResID::Sound_AxeHit_1)->second, 0);
		break;
	case 1:
		Mix_PlayChannel(-1, soundPool.find(ResID::Sound_AxeHit_2)->second, 0);
		break;
	case 2:
		Mix_PlayChannel(-1, soundPool.find(ResID::Sound_AxeHit_3)->second, 0);
		break;
	}

	enemy->slowDown();

	Bullet::onCollide(enemy);
}
