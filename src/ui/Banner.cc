#include "Banner.h"

Banner::Banner()
{
	m_sizeForeground = { 646, 215 };
	m_sizeBackground = { 1282, 209 };

	m_timerDisplay.setOneShot(true);
	m_timerDisplay.setWaitTime(5);
	m_timerDisplay.setOnTimeout([&]() { m_isEndDisplay = true; });
}

void Banner::setCenterPosition(const TwoVector& pos)
{
	m_posCenter = pos;
}

void Banner::onUpdate(double delta)
{
	m_timerDisplay.onUpdate(delta);

	const ResourcesManager::TexturePool& texPool = ResourcesManager::instance()->getTexturePool();
	const ConfigManager* instance = ConfigManager::instance();

	m_texForeground = texPool.find(instance->m_isGameWin ? ResID::Tex_UIWinText : ResID::Tex_UILossText)->second;
	m_texBackground = texPool.find(ResID::Tex_UIGameOverBar)->second;
}

void Banner::onRender(SDL_Renderer* renderer)
{
	static SDL_Rect rectDst;

	rectDst.x = (int)(m_posCenter.m_x - m_sizeBackground.m_x / 2);
	rectDst.y = (int)(m_posCenter.m_y - m_sizeBackground.m_y / 2);
	rectDst.w = (int)m_sizeBackground.m_x, rectDst.h = (int)m_sizeBackground.m_y;
	SDL_RenderCopy(renderer, m_texBackground, nullptr, &rectDst);

	rectDst.x = (int)(m_posCenter.m_x - m_sizeForeground.m_x / 2);
	rectDst.y = (int)(m_posCenter.m_y - m_sizeForeground.m_y / 2);
	rectDst.w = (int)m_sizeForeground.m_x, rectDst.h = (int)m_sizeForeground.m_y;
	SDL_RenderCopy(renderer, m_texForeground, nullptr, &rectDst);
}

bool Banner::checkEndDispaly()
{
	return m_isEndDisplay;
}