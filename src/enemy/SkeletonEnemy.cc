#include "SkeletonEnemy.h"

SkeletonEnemy::SkeletonEnemy()
{
	static const ResourcesManager::TexturePool& texturePool = ResourcesManager::instance()->getTexturePool();
	static SDL_Texture* texSkeleton = texturePool.find(ResID::Tex_Skeleton)->second;
	static SDL_Texture* texSkeletonSketch = texturePool.find(ResID::Tex_SkeletonSketch)->second;
	static ConfigManager::EnemyTemplate& skeletonTemplate = ConfigManager::instance()->m_skeletonTemplate;

	static const std::vector<int> idxListUp = { 5, 6, 7, 8, 9 };
	static const std::vector<int> idxListDown = { 0, 1, 2, 3, 4 };
	static const std::vector<int> idxListLeft = { 15, 16, 17, 18, 19 };
	static const std::vector<int> idxListRight = { 10, 11, 12, 13, 14 };

	m_animUp.setLoop(true); m_animUp.setInterval(0.15);
	m_animUp.setFrameData(texSkeleton, 5, 4, idxListUp);
	m_animDown.setLoop(true); m_animDown.setInterval(0.15);
	m_animDown.setFrameData(texSkeleton, 5, 4, idxListDown);
	m_animLeft.setLoop(true); m_animLeft.setInterval(0.15);
	m_animLeft.setFrameData(texSkeleton, 5, 4, idxListLeft);
	m_animRight.setLoop(true); m_animRight.setInterval(0.15);
	m_animRight.setFrameData(texSkeleton, 5, 4, idxListRight);

	m_animUpSketch.setLoop(true); m_animUpSketch.setInterval(0.15);
	m_animUpSketch.setFrameData(texSkeletonSketch, 5, 4, idxListUp);
	m_animDownSketch.setLoop(true); m_animDownSketch.setInterval(0.15);
	m_animDownSketch.setFrameData(texSkeletonSketch, 5, 4, idxListDown);
	m_animLeftSketch.setLoop(true); m_animLeftSketch.setInterval(0.15);
	m_animLeftSketch.setFrameData(texSkeletonSketch, 5, 4, idxListLeft);
	m_animRightSketch.setLoop(true); m_animRightSketch.setInterval(0.15);
	m_animRightSketch.setFrameData(texSkeletonSketch, 5, 4, idxListRight);

	m_maxHp = skeletonTemplate.m_hp;
	m_maxSpeed = skeletonTemplate.m_speed;
	m_damage = skeletonTemplate.m_damage;
	m_rewardRatio = skeletonTemplate.m_rewardRatio;
	m_recoverInterval = skeletonTemplate.m_recoverInterval;
	m_recoverRange = skeletonTemplate.m_recoverRange;
	m_recoverIntensity = skeletonTemplate.m_recoverIntensity;

	m_size.m_x = 48, m_size.m_y = 48;
	m_hp = m_maxHp, m_speed = m_maxSpeed;
}