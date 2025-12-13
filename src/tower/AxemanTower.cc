#include "AxemanTower.h"

AxemanTower::AxemanTower()
{
	static SDL_Texture* texAxeman = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_Axeman)->second;

	static const std::vector<int> idx_list_idle_up = { 3, 4 };
	static const std::vector<int> idx_list_idle_down = { 0, 1 };
	static const std::vector<int> idx_list_idle_left = { 9, 10 };
	static const std::vector<int> idx_list_idle_right = { 6, 7 };
	static const std::vector<int> idx_list_fire_up = { 15, 16, 17 };
	static const std::vector<int> idx_list_fire_down = { 12, 13, 14 };
	static const std::vector<int> idx_list_fire_left = { 21, 22, 23 };
	static const std::vector<int> idx_list_fire_right = { 18, 19, 20 };

	m_animIdleUp.setFrameData(texAxeman, 3, 8, idx_list_idle_up);
	m_animIdleDown.setFrameData(texAxeman, 3, 8, idx_list_idle_down);
	m_animIdleLeft.setFrameData(texAxeman, 3, 8, idx_list_idle_left);
	m_animIdleRight.setFrameData(texAxeman, 3, 8, idx_list_idle_right);
	m_animFireUp.setFrameData(texAxeman, 3, 8, idx_list_fire_up);
	m_animFireDown.setFrameData(texAxeman, 3, 8, idx_list_fire_down);
	m_animFireLeft.setFrameData(texAxeman, 3, 8, idx_list_fire_left);
	m_animFireRight.setFrameData(texAxeman, 3, 8, idx_list_fire_right);

	m_size.m_x = 48, m_size.m_y = 48;

	m_towerType = TowerType::Axeman;

	m_fireSpeed = 5;
	m_bulletType = BulletType::Axe;
}