#include "StatusBar.h"

void StatusBar::setPosition(int x, int y)
{
	m_position.x = x, m_position.y = y;
}

void StatusBar::onUpdate(SDL_Renderer* renderer)
{
	static TTF_Font* font = ResourcesManager::instance()->getFontPool().find(ResID::Font_Main)->second;

	SDL_DestroyTexture(m_texTextBackground);
	m_texTextBackground = nullptr;
	SDL_DestroyTexture(m_texTextForeground);
	m_texTextForeground = nullptr;

	std::string strVal = std::to_string((int)CoinManager::instance()->getCurrentCoinNum());
	SDL_Surface* sufTextBackground = TTF_RenderText_Blended(font, strVal.c_str(), m_colorTextBackground);
	SDL_Surface* sufTextForeground = TTF_RenderText_Blended(font, strVal.c_str(), m_colorTextForeground);

	m_widthText = sufTextBackground->w, m_heightText = sufTextBackground->h;

	m_texTextBackground = SDL_CreateTextureFromSurface(renderer, sufTextBackground);
	m_texTextForeground = SDL_CreateTextureFromSurface(renderer, sufTextForeground);

	SDL_FreeSurface(sufTextBackground);
	SDL_FreeSurface(sufTextForeground);
}

void StatusBar::onRender(SDL_Renderer* renderer)
{
	static SDL_Rect rectDst;
	static const ResourcesManager::TexturePool& texPool = ResourcesManager::instance()->getTexturePool();
	static SDL_Texture* texCoin = texPool.find(ResID::Tex_UICoin)->second;
	static SDL_Texture* texHeart = texPool.find(ResID::Tex_UIHeart)->second;
	static SDL_Texture* texHomeAvatar = texPool.find(ResID::Tex_UIHomeAvatar)->second;
	static SDL_Texture* texPlayerAvatar = texPool.find(ResID::Tex_UIPlayerAvatar)->second;

	rectDst.x = m_position.x, rectDst.y = m_position.y;
	rectDst.w = 78, rectDst.h = 78;
	SDL_RenderCopy(renderer, texHomeAvatar, nullptr, &rectDst);

	for (int i = 0; i < (int)HomeManager::instance()->getCurrentHpNum(); i++)
	{
		rectDst.x = m_position.x + 78 + 15 + i * (32 + 2);
		rectDst.y = m_position.y;
		rectDst.w = 32, rectDst.h = 32;
		SDL_RenderCopy(renderer, texHeart, nullptr, &rectDst);
	}

	rectDst.x = m_position.x + 78 + 15;
	rectDst.y = m_position.y + 78 - 32;
	rectDst.w = 32, rectDst.h = 32;
	SDL_RenderCopy(renderer, texCoin, nullptr, &rectDst);

	rectDst.x += 32 + 10 + m_offsetShadow.x;
	rectDst.y = rectDst.y + (32 - m_heightText) / 2 + m_offsetShadow.y;
	rectDst.w = m_widthText, rectDst.h = m_heightText;
	SDL_RenderCopy(renderer, m_texTextBackground, nullptr, &rectDst);

	rectDst.x -= m_offsetShadow.x;
	rectDst.y -= m_offsetShadow.y;
	SDL_RenderCopy(renderer, m_texTextForeground, nullptr, &rectDst);

	rectDst.x = m_position.x + (78 - 65) / 2;
	rectDst.y = m_position.y + 78 + 5;
	rectDst.w = 65, rectDst.h = 65;
	SDL_RenderCopy(renderer, texPlayerAvatar, nullptr, &rectDst);

	rectDst.x = m_position.x + 78 + 15;
	rectDst.y += 10;
	roundedBoxRGBA(renderer, rectDst.x, rectDst.y, rectDst.x + m_widthMpBar, rectDst.y + m_heightMpBar, 4,
		m_colorMpBarBackground.r, m_colorMpBarBackground.g, m_colorMpBarBackground.b, m_colorMpBarBackground.a);

	rectDst.x += m_widthBorderMpBar;
	rectDst.y += m_widthBorderMpBar;
	rectDst.w = m_widthMpBar - 2 * m_widthBorderMpBar;
	rectDst.h = m_heightMpBar - 2 * m_widthBorderMpBar;
	double process = PlayerManager::instance()->getCurrentMp() / 100;
	roundedBoxRGBA(renderer, rectDst.x, rectDst.y, rectDst.x + (int)(rectDst.w * process), rectDst.y + rectDst.h, 2,
		m_colorMpBarForedground.r, m_colorMpBarForedground.g, m_colorMpBarForedground.b, m_colorMpBarForedground.a);
}