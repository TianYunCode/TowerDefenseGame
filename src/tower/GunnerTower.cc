#include "GunnerTower.h"

GunnerTower::GunnerTower()
{
	static SDL_Texture* texGunner = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_Gunner)->second;

	static const std::vector<int> idx_list_idle_up = { 4, 5 };
	static const std::vector<int> idx_list_idle_down = { 0, 1 };
	static const std::vector<int> idx_list_idle_left = { 12, 13 };
	static const std::vector<int> idx_list_idle_right = { 8, 9 };
	static const std::vector<int> idx_list_fire_up = { 20, 21, 22, 23 };
	static const std::vector<int> idx_list_fire_down = { 16, 17, 18, 19 };
	static const std::vector<int> idx_list_fire_left = { 28, 29, 30, 31 };
	static const std::vector<int> idx_list_fire_right = { 24, 25, 26, 27 };

	m_animIdleUp.setFrameData(texGunner, 4, 8, idx_list_idle_up);
	m_animIdleDown.setFrameData(texGunner, 4, 8, idx_list_idle_down);
	m_animIdleLeft.setFrameData(texGunner, 4, 8, idx_list_idle_left);
	m_animIdleRight.setFrameData(texGunner, 4, 8, idx_list_idle_right);
	m_animFireUp.setFrameData(texGunner, 4, 8, idx_list_fire_up);
	m_animFireDown.setFrameData(texGunner, 4, 8, idx_list_fire_down);
	m_animFireLeft.setFrameData(texGunner, 4, 8, idx_list_fire_left);
	m_animFireRight.setFrameData(texGunner, 4, 8, idx_list_fire_right);

	m_size.m_x = 48, m_size.m_y = 48;

	m_towerType = TowerType::Gunner;

	m_fireSpeed = 6;
	m_bulletType = BulletType::Shell;
}