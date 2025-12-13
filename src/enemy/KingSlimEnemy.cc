#include "KingSlimEnemy.h"

KingSlimeEnemy::KingSlimeEnemy()
{
	static const ResourcesManager::TexturePool& texturePool = ResourcesManager::instance()->getTexturePool();
	static SDL_Texture* texKingSlime = texturePool.find(ResID::Tex_KingSlime)->second;
	static SDL_Texture* texKingSlimeSketch = texturePool.find(ResID::Tex_KingSlimeSketch)->second;
	static ConfigManager::EnemyTemplate& kingSlimTemplate = ConfigManager::instance()->m_kingSlimTemplate;

	static const std::vector<int> idxListUp = { 18, 19, 20, 21, 22, 23 };
	static const std::vector<int> idxListDown = { 0, 1, 2, 3, 4, 5 };
	static const std::vector<int> idxListLeft = { 6, 7, 8, 9, 10, 11 };
	static const std::vector<int> idxListRight = { 12, 13, 14, 15, 16, 17 };

	m_animUp.setLoop(true); m_animUp.setInterval(0.1);
	m_animUp.setFrameData(texKingSlime, 6, 4, idxListUp);
	m_animDown.setLoop(true); m_animDown.setInterval(0.1);
	m_animDown.setFrameData(texKingSlime, 6, 4, idxListDown);
	m_animLeft.setLoop(true); m_animLeft.setInterval(0.1);
	m_animLeft.setFrameData(texKingSlime, 6, 4, idxListLeft);
	m_animRight.setLoop(true); m_animRight.setInterval(0.1);
	m_animRight.setFrameData(texKingSlime, 6, 4, idxListRight);

	m_animUpSketch.setLoop(true); m_animUpSketch.setInterval(0.1);
	m_animUpSketch.setFrameData(texKingSlimeSketch, 6, 4, idxListUp);
	m_animDownSketch.setLoop(true); m_animDownSketch.setInterval(0.1);
	m_animDownSketch.setFrameData(texKingSlimeSketch, 6, 4, idxListDown);
	m_animLeftSketch.setLoop(true); m_animLeftSketch.setInterval(0.1);
	m_animLeftSketch.setFrameData(texKingSlimeSketch, 6, 4, idxListLeft);
	m_animRightSketch.setLoop(true); m_animRightSketch.setInterval(0.1);
	m_animRightSketch.setFrameData(texKingSlimeSketch, 6, 4, idxListRight);

	m_maxHp = kingSlimTemplate.m_hp;
	m_maxSpeed = kingSlimTemplate.m_speed;
	m_damage = kingSlimTemplate.m_damage;
	m_rewardRatio = kingSlimTemplate.m_rewardRatio;
	m_recoverInterval = kingSlimTemplate.m_recoverInterval;
	m_recoverRange = kingSlimTemplate.m_recoverRange;
	m_recoverIntensity = kingSlimTemplate.m_recoverIntensity;

	m_size.m_x = 48, m_size.m_y = 48;
	m_hp = m_maxHp, m_speed = m_maxSpeed;
}