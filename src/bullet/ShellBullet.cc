#include "ShellBullet.h"

ShellBullet::ShellBullet()
{
	static SDL_Texture* texShell = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_BulletShell)->second;
	static SDL_Texture* texExplode = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_EffectExplode)->second;

	static const std::vector<int> idxList = { 0, 1 };
	static const std::vector<int> idxExplodeList = { 0, 1, 2, 3, 4 };

	m_animation.setLoop(true);
	m_animation.setInterval(0.1);
	m_animation.setFrameData(texShell, 2, 1, idxList);

	m_animationExplode.setLoop(false);
	m_animationExplode.setInterval(0.1);
	m_animationExplode.setFrameData(texExplode, 5, 1, idxExplodeList);
	m_animationExplode.setOnFinished([&]() { makeInvalid(); });

	m_damageRange = 96;
	m_size.m_x = 48, m_size.m_y = 48;
}

void ShellBullet::onUpdate(double delta)
{
	if (canCollide())
	{
		Bullet::onUpdate(delta);
		return;
	}

	m_animationExplode.onUpdate(delta);
}

void ShellBullet::onRender(SDL_Renderer* renderer)
{
	if (canCollide())
	{
		Bullet::onRender(renderer);
		return;
	}

	static SDL_Point point;

	point.x = (int)(m_position.m_x - 96 / 2);
	point.y = (int)(m_position.m_y - 96 / 2);

	m_animationExplode.onRender(renderer, point);
}

void ShellBullet::onCollide(Enemy* enemy)
{
	static const ResourcesManager::SoundPool& soundPool = ResourcesManager::instance()->getSoundPool();

	Mix_PlayChannel(-1, soundPool.find(ResID::Sound_ShellHit)->second, 0);

	disableCollide();
}