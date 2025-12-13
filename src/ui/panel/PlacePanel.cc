#include "PlacePanel.h"

PlacePanel::PlacePanel()
{
	const ResourcesManager::TexturePool& texturePool = ResourcesManager::instance()->getTexturePool();

	m_texIdle = texturePool.find(ResID::Tex_UIPlaceIdle)->second;
	m_texHoveredTop = texturePool.find(ResID::Tex_UIPlaceHoveredTop)->second;
	m_texHoveredLeft = texturePool.find(ResID::Tex_UIPlaceHoveredLeft)->second;
	m_texHoveredRight = texturePool.find(ResID::Tex_UIPlaceHoveredRight)->second;
}

void PlacePanel::onUpdate(SDL_Renderer* renderer)
{
	static TowerManager* instance = TowerManager::instance();

	m_valTop = (int)instance->getPlaceCost(TowerType::Axeman);
	m_valLeft = (int)instance->getPlaceCost(TowerType::Archer);
	m_valRight = (int)instance->getPlaceCost(TowerType::Gunner);

	m_regTop = (int)instance->getDamageRange(TowerType::Axeman) * SIZE_TILE;
	m_regLeft = (int)instance->getDamageRange(TowerType::Archer) * SIZE_TILE;
	m_regRight = (int)instance->getDamageRange(TowerType::Gunner) * SIZE_TILE;

	Panel::onUpdate(renderer);
}

void PlacePanel::onRender(SDL_Renderer* renderer)
{
	if (!m_visible)
	{
		return;
	}

	int reg = 0;
	switch (m_hoveredTarget)
	{
	case Panel::HoveredTarget::Top:
		reg = m_regTop;
		break;
	case Panel::HoveredTarget::Left:
		reg = m_regLeft;
		break;
	case Panel::HoveredTarget::Right:
		reg = m_regRight;
		break;
	}

	if (reg > 0)
	{
		filledCircleRGBA(renderer, m_centerPos.x, m_centerPos.y, reg, m_colorRegionContent.r, m_colorRegionContent.g, m_colorRegionContent.b, m_colorRegionContent.a);
		aacircleRGBA(renderer, m_centerPos.x, m_centerPos.y, reg, m_colorRegionFrame.r, m_colorRegionFrame.g, m_colorRegionFrame.b, m_colorRegionFrame.a);
	}

	Panel::onRender(renderer);
}

void PlacePanel::onClickTopArea()
{
	CoinManager* instance = CoinManager::instance();

	if (m_valTop <= instance->getCurrentCoinNum())
	{
		TowerManager::instance()->placeTower(TowerType::Axeman, m_idxTileSelected);
		instance->decreaseCoin(m_valTop);
	}
}

void PlacePanel::onClickLeftArea()
{
	CoinManager* instance = CoinManager::instance();

	if (m_valLeft <= instance->getCurrentCoinNum())
	{
		TowerManager::instance()->placeTower(TowerType::Archer, m_idxTileSelected);
		instance->decreaseCoin(m_valLeft);
	}
}

void PlacePanel::onClickRightArea()
{
	CoinManager* instance = CoinManager::instance();

	if (m_valRight <= instance->getCurrentCoinNum())
	{
		TowerManager::instance()->placeTower(TowerType::Gunner, m_idxTileSelected);
		instance->decreaseCoin(m_valRight);
	}
}