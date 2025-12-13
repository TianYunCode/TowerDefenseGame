#include "SlimEnemy.h"

SlimEnemy::SlimEnemy()
{
	static const ResourcesManager::TexturePool& texturePool = ResourcesManager::instance()->getTexturePool();
	static SDL_Texture* texSlime = texturePool.find(ResID::Tex_Slime)->second;
	static SDL_Texture* texSlimeSketch = texturePool.find(ResID::Tex_SlimeSketch)->second;
	static ConfigManager::EnemyTemplate& slimTemplate = ConfigManager::instance()->m_slimTemplate;

	static const std::vector<int> idxListUp = { 6, 7, 8, 9, 10, 11 };
	static const std::vector<int> idxListDown = { 0, 1, 2, 3, 4, 5 };
	static const std::vector<int> idxListLeft = { 18, 19, 20, 21, 22, 23 };
	static const std::vector<int> idxListRight = { 12, 13, 14, 15, 16, 17 };

	m_animUp.setLoop(true); m_animUp.setInterval(0.1);
	m_animUp.setFrameData(texSlime, 6, 4, idxListUp);
	m_animDown.setLoop(true); m_animDown.setInterval(0.1);
	m_animDown.setFrameData(texSlime, 6, 4, idxListDown);
	m_animLeft.setLoop(true); m_animLeft.setInterval(0.1);
	m_animLeft.setFrameData(texSlime, 6, 4, idxListLeft);
	m_animRight.setLoop(true); m_animRight.setInterval(0.1);
	m_animRight.setFrameData(texSlime, 6, 4, idxListRight);

	m_animUpSketch.setLoop(true); m_animUpSketch.setInterval(0.1);
	m_animUpSketch.setFrameData(texSlimeSketch, 6, 4, idxListUp);
	m_animDownSketch.setLoop(true); m_animDownSketch.setInterval(0.1);
	m_animDownSketch.setFrameData(texSlimeSketch, 6, 4, idxListDown);
	m_animLeftSketch.setLoop(true); m_animLeftSketch.setInterval(0.1);
	m_animLeftSketch.setFrameData(texSlimeSketch, 6, 4, idxListLeft);
	m_animRightSketch.setLoop(true); m_animRightSketch.setInterval(0.1);
	m_animRightSketch.setFrameData(texSlimeSketch, 6, 4, idxListRight);

	m_maxHp = slimTemplate.m_hp;
	m_maxSpeed = slimTemplate.m_speed;
	m_damage = slimTemplate.m_damage;
	m_rewardRatio = slimTemplate.m_rewardRatio;
	m_recoverInterval = slimTemplate.m_recoverInterval;
	m_recoverRange = slimTemplate.m_recoverRange;
	m_recoverIntensity = slimTemplate.m_recoverIntensity;

	m_size.m_x = 48, m_size.m_y = 48;
	m_hp = m_maxHp, m_speed = m_maxSpeed;
}