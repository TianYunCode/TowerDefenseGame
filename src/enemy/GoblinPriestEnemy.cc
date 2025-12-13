#include "GoblinPriestEnemy.h"

GoblinPriestEnemy::GoblinPriestEnemy()
{
	static const ResourcesManager::TexturePool& texturePool = ResourcesManager::instance()->getTexturePool();
	static SDL_Texture* texGoblinPriest = texturePool.find(ResID::Tex_GoblinPriest)->second;
	static SDL_Texture* texGoblinPriestSketch = texturePool.find(ResID::Tex_GoblinPriestSketch)->second;
	static ConfigManager::EnemyTemplate& goblinPriestTemplate = ConfigManager::instance()->m_goblinPriestTemplate;

	static const std::vector<int> idxListUp = { 5, 6, 7, 8, 9 };
	static const std::vector<int> idxListDown = { 0, 1, 2, 3, 4 };
	static const std::vector<int> idxListLeft = { 15, 16, 17, 18, 19 };
	static const std::vector<int> idxListRight = { 10, 11, 12, 13, 14 };

	m_animUp.setLoop(true); m_animUp.setInterval(0.15);
	m_animUp.setFrameData(texGoblinPriest, 5, 4, idxListUp);
	m_animDown.setLoop(true); m_animDown.setInterval(0.15);
	m_animDown.setFrameData(texGoblinPriest, 5, 4, idxListDown);
	m_animLeft.setLoop(true); m_animLeft.setInterval(0.15);
	m_animLeft.setFrameData(texGoblinPriest, 5, 4, idxListLeft);
	m_animRight.setLoop(true); m_animRight.setInterval(0.15);
	m_animRight.setFrameData(texGoblinPriest, 5, 4, idxListRight);

	m_animUpSketch.setLoop(true); m_animUpSketch.setInterval(0.15);
	m_animUpSketch.setFrameData(texGoblinPriestSketch, 5, 4, idxListUp);
	m_animDownSketch.setLoop(true); m_animDownSketch.setInterval(0.15);
	m_animDownSketch.setFrameData(texGoblinPriestSketch, 5, 4, idxListDown);
	m_animLeftSketch.setLoop(true); m_animLeftSketch.setInterval(0.15);
	m_animLeftSketch.setFrameData(texGoblinPriestSketch, 5, 4, idxListLeft);
	m_animRightSketch.setLoop(true); m_animRightSketch.setInterval(0.15);
	m_animRightSketch.setFrameData(texGoblinPriestSketch, 5, 4, idxListRight);

	m_maxHp = goblinPriestTemplate.m_hp;
	m_maxSpeed = goblinPriestTemplate.m_speed;
	m_damage = goblinPriestTemplate.m_damage;
	m_rewardRatio = goblinPriestTemplate.m_rewardRatio;
	m_recoverInterval = goblinPriestTemplate.m_recoverInterval;
	m_recoverRange = goblinPriestTemplate.m_recoverRange;
	m_recoverIntensity = goblinPriestTemplate.m_recoverIntensity;

	m_size.m_x = 48, m_size.m_y = 48;
	m_hp = m_maxHp, m_speed = m_maxSpeed;

	m_timerSkill.setWaitTime(m_recoverInterval);
}