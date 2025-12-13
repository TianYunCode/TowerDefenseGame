#include "ArcherTower.h"

ArcherTower::ArcherTower()
{
	static SDL_Texture* texArcher = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_Archer)->second;

	static const std::vector<int> idx_list_idle_up = { 3, 4 };
	static const std::vector<int> idx_list_idle_down = { 0, 1 };
	static const std::vector<int> idx_list_idle_left = { 6, 7 };
	static const std::vector<int> idx_list_idle_right = { 9, 10 };
	static const std::vector<int> idx_list_fire_up = { 15, 16, 17 };
	static const std::vector<int> idx_list_fire_down = { 12, 13, 14 };
	static const std::vector<int> idx_list_fire_left = { 18, 19, 20 };
	static const std::vector<int> idx_list_fire_right = { 21, 22, 23 };

	m_animIdleUp.setFrameData(texArcher, 3, 8, idx_list_idle_up);
	m_animIdleDown.setFrameData(texArcher, 3, 8, idx_list_idle_down);
	m_animIdleLeft.setFrameData(texArcher, 3, 8, idx_list_idle_left);
	m_animIdleRight.setFrameData(texArcher, 3, 8, idx_list_idle_right);
	m_animFireUp.setFrameData(texArcher, 3, 8, idx_list_fire_up);
	m_animFireDown.setFrameData(texArcher, 3, 8, idx_list_fire_down);
	m_animFireLeft.setFrameData(texArcher, 3, 8, idx_list_fire_left);
	m_animFireRight.setFrameData(texArcher, 3, 8, idx_list_fire_right);

	m_size.m_x = 48, m_size.m_y = 48;

	m_towerType = TowerType::Archer;

	m_fireSpeed = 6;
	m_bulletType = BulletType::Arrow;
}