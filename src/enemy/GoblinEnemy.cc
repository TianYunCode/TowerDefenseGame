#include "GoblinEnemy.h"

GoblinEnemy::GoblinEnemy()
{
	static const ResourcesManager::TexturePool& texturePool = ResourcesManager::instance()->getTexturePool();
	static SDL_Texture* texGoblin = texturePool.find(ResID::Tex_Goblin)->second;
	static SDL_Texture* texGoblinSketch = texturePool.find(ResID::Tex_GoblinSketch)->second;
	static ConfigManager::EnemyTemplate& goblinTemplate = ConfigManager::instance()->m_goblinTemplate;

	static const std::vector<int> idxListUp = { 5, 6, 7, 8, 9 };
	static const std::vector<int> idxListDown = { 0, 1, 2, 3, 4 };
	static const std::vector<int> idxListLeft = { 15, 16, 17, 18, 19 };
	static const std::vector<int> idxListRight = { 10, 11, 12, 13, 14 };

	m_animUp.setLoop(true); m_animUp.setInterval(0.15);
	m_animUp.setFrameData(texGoblin, 5, 4, idxListUp);
	m_animDown.setLoop(true); m_animDown.setInterval(0.15);
	m_animDown.setFrameData(texGoblin, 5, 4, idxListDown);
	m_animLeft.setLoop(true); m_animLeft.setInterval(0.15);
	m_animLeft.setFrameData(texGoblin, 5, 4, idxListLeft);
	m_animRight.setLoop(true); m_animRight.setInterval(0.15);
	m_animRight.setFrameData(texGoblin, 5, 4, idxListRight);

	m_animUpSketch.setLoop(true); m_animUpSketch.setInterval(0.15);
	m_animUpSketch.setFrameData(texGoblinSketch, 5, 4, idxListUp);
	m_animDownSketch.setLoop(true); m_animDownSketch.setInterval(0.15);
	m_animDownSketch.setFrameData(texGoblinSketch, 5, 4, idxListDown);
	m_animLeftSketch.setLoop(true); m_animLeftSketch.setInterval(0.15);
	m_animLeftSketch.setFrameData(texGoblinSketch, 5, 4, idxListLeft);
	m_animRightSketch.setLoop(true); m_animRightSketch.setInterval(0.15);
	m_animRightSketch.setFrameData(texGoblinSketch, 5, 4, idxListRight);

	m_maxHp = goblinTemplate.m_hp;
	m_maxSpeed = goblinTemplate.m_speed;
	m_damage = goblinTemplate.m_damage;
	m_rewardRatio = goblinTemplate.m_rewardRatio;
	m_recoverInterval = goblinTemplate.m_recoverInterval;
	m_recoverRange = goblinTemplate.m_recoverRange;
	m_recoverIntensity = goblinTemplate.m_recoverIntensity;

	m_size.m_x = 48, m_size.m_y = 48;
	m_hp = m_maxHp, m_speed = m_maxSpeed;
}