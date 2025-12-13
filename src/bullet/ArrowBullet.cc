#include "ArrowBullet.h"

ArrowBullet::ArrowBullet()
{
	static SDL_Texture* texArrow = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_BulletArrow)->second;

	static const std::vector<int> idxList = { 0, 1 };

	m_animation.setLoop(true);
	m_animation.setInterval(0.1);
	m_animation.setFrameData(texArrow, 2, 1, idxList);

	m_canRotated = true;
	m_size.m_x = 48, m_size.m_y = 48;
}

void ArrowBullet::onCollide(Enemy* enemy)
{
	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	switch (rand() % 3)
	{
	case 0:
		Mix_PlayChannel(-1, soundPool.find(ResID::Sound_ArrowHit_1)->second, 0);
		break;
	case 1:
		Mix_PlayChannel(-1, soundPool.find(ResID::Sound_ArrowHit_2)->second, 0);
		break;
	case 2:
		Mix_PlayChannel(-1, soundPool.find(ResID::Sound_ArrowHit_3)->second, 0);
		break;
	}

	Bullet::onCollide(enemy);
}
