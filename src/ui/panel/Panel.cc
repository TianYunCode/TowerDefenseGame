#include "Panel.h"

Panel::Panel()
{
	m_texSelectCursor = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_UISelectCursor)->second;
}

Panel::~Panel()
{
	SDL_DestroyTexture(m_texTextBackground);
	SDL_DestroyTexture(m_texTextForeground);
}

void Panel::show()
{
	m_visible = true;
}

void Panel::setIdxTile(const SDL_Point& idx)
{
	m_idxTileSelected = idx;
}

void Panel::setCenterPos(const SDL_Point& pos)
{
	m_centerPos = pos;
}

void Panel::onInput(const SDL_Event& event)
{
	if (!m_visible)
	{
		return;
	}

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
	{
		SDL_Point posCursor = { event.motion.x, event.motion.y };
		SDL_Rect rectTarget = { 0, 0, m_sizeButton, m_sizeButton };

		rectTarget.x = m_centerPos.x - m_width / 2 + m_offsetTop.x;
		rectTarget.y = m_centerPos.y - m_width / 2 + m_offsetTop.y;
		if (SDL_PointInRect(&posCursor, &rectTarget))
		{
			m_hoveredTarget = HoveredTarget::Top;
			return;
		}

		rectTarget.x = m_centerPos.x - m_width / 2 + m_offsetLeft.x;
		rectTarget.y = m_centerPos.y - m_width / 2 + m_offsetLeft.y;
		if (SDL_PointInRect(&posCursor, &rectTarget))
		{
			m_hoveredTarget = HoveredTarget::Left;
			return;
		}

		rectTarget.x = m_centerPos.x - m_width / 2 + m_offsetRight.x;
		rectTarget.y = m_centerPos.y - m_width / 2 + m_offsetRight.y;
		if (SDL_PointInRect(&posCursor, &rectTarget))
		{
			m_hoveredTarget = HoveredTarget::Right;
			return;
		}

		m_hoveredTarget = HoveredTarget::None;
	}
	break;
	case SDL_MOUSEBUTTONUP:
	{
		switch (m_hoveredTarget)
		{
		case Panel::HoveredTarget::Top:
			onClickTopArea();
			break;
		case Panel::HoveredTarget::Left:
			onClickLeftArea();
			break;
		case Panel::HoveredTarget::Right:
			onClickRightArea();
			break;
		}

		m_visible = false;
	}
	break;
	default:
		break;
	}
}

void Panel::onUpdate(SDL_Renderer* renderer)
{
	static TTF_Font* font = ResourcesManager::instance()->getFontPool().find(ResID::Font_Main)->second;

	if (m_hoveredTarget == HoveredTarget::None)
	{
		return;
	}

	int val = 0;
	switch (m_hoveredTarget)
	{
	case Panel::HoveredTarget::Top:
		val = m_valTop;
		break;
	case Panel::HoveredTarget::Left:
		val = m_valLeft;
		break;
	case Panel::HoveredTarget::Right:
		val = m_valRight;
		break;
	}

	SDL_DestroyTexture(m_texTextBackground);
	m_texTextBackground = nullptr;
	SDL_DestroyTexture(m_texTextForeground);
	m_texTextForeground = nullptr;

	std::string strVal = val < 0 ? "MAX" : std::to_string(val);
	SDL_Surface* sufTextBackground = TTF_RenderText_Blended(font, strVal.c_str(), m_colorTextBackground);
	SDL_Surface* sufTextForeground = TTF_RenderText_Blended(font, strVal.c_str(), m_colorTextForeground);

	m_widthText = sufTextBackground->w, m_heightText = sufTextBackground->h;
	m_texTextBackground = SDL_CreateTextureFromSurface(renderer, sufTextBackground);
	m_texTextForeground = SDL_CreateTextureFromSurface(renderer, sufTextForeground);

	SDL_FreeSurface(sufTextBackground);
	SDL_FreeSurface(sufTextForeground);
}

void Panel::onRender(SDL_Renderer* renderer)
{
	if (!m_visible)
	{
		return;
	}

	SDL_Rect rectDstCursor =
	{
		m_centerPos.x - SIZE_TILE / 2,
		m_centerPos.y - SIZE_TILE / 2,
		SIZE_TILE, SIZE_TILE
	};
	SDL_RenderCopy(renderer, m_texSelectCursor, nullptr, &rectDstCursor);

	SDL_Rect rectDstPanel =
	{
		m_centerPos.x - m_width / 2,
		m_centerPos.y - m_height / 2,
		m_width, m_height
	};

	SDL_Texture* texPanel = nullptr;
	switch (m_hoveredTarget)
	{
	case Panel::HoveredTarget::None:
		texPanel = m_texIdle;
		break;
	case Panel::HoveredTarget::Top:
		texPanel = m_texHoveredTop;
		break;
	case Panel::HoveredTarget::Left:
		texPanel = m_texHoveredLeft;
		break;
	case Panel::HoveredTarget::Right:
		texPanel = m_texHoveredRight;
		break;
	}

	SDL_RenderCopy(renderer, texPanel, nullptr, &rectDstPanel);

	if (m_hoveredTarget == HoveredTarget::None)
	{
		return;
	}

	SDL_Rect rectDstText;

	rectDstText.x = m_centerPos.x - m_widthText / 2 + m_offsetShadow.x;
	rectDstText.y = m_centerPos.y + m_height / 2 + m_offsetShadow.y;
	rectDstText.w = m_widthText, rectDstText.h = m_heightText;
	SDL_RenderCopy(renderer, m_texTextBackground, nullptr, &rectDstText);

	rectDstText.x -= m_offsetShadow.x;
	rectDstText.y -= m_offsetShadow.y;
	SDL_RenderCopy(renderer, m_texTextForeground, nullptr, &rectDstText);
}
