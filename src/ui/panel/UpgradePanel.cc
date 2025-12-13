#include "UpgradePanel.h"

UpgradePanel::UpgradePanel()
{
	const ResourcesManager::TexturePool& texturePool = ResourcesManager::instance()->getTexturePool();

	m_texIdle = texturePool.find(ResID::Tex_UIUpgradeIdle)->second;
	m_texHoveredTop = texturePool.find(ResID::Tex_UIUpgradeHoveredTop)->second;
	m_texHoveredLeft = texturePool.find(ResID::Tex_UIUpgradeHoveredLeft)->second;
	m_texHoveredRight = texturePool.find(ResID::Tex_UIUpgradeHoveredRight)->second;
}

void UpgradePanel::onUpdate(SDL_Renderer* renderer)
{
	static TowerManager* instance = TowerManager::instance();

	m_valTop = (int)instance->getUpgradeCost(TowerType::Axeman);
	m_valLeft = (int)instance->getUpgradeCost(TowerType::Archer);
	m_valRight = (int)instance->getUpgradeCost(TowerType::Gunner);

	Panel::onUpdate(renderer);
}

void UpgradePanel::onClickTopArea()
{
	CoinManager* instance = CoinManager::instance();

	if (m_valTop > 0 && m_valTop <= instance->getCurrentCoinNum())
	{
		TowerManager::instance()->upgradeTower(TowerType::Axeman);
		instance->decreaseCoin(m_valTop);
	}
}

void UpgradePanel::onClickLeftArea()
{
	CoinManager* instance = CoinManager::instance();

	if (m_valLeft > 0 && m_valLeft <= instance->getCurrentCoinNum())
	{
		TowerManager::instance()->upgradeTower(TowerType::Axeman);
		instance->decreaseCoin(m_valLeft);
	}
}

void UpgradePanel::onClickRightArea()
{
	CoinManager* instance = CoinManager::instance();

	if (m_valRight > 0 && m_valRight <= instance->getCurrentCoinNum())
	{
		TowerManager::instance()->upgradeTower(TowerType::Axeman);
		instance->decreaseCoin(m_valRight);
	}
}