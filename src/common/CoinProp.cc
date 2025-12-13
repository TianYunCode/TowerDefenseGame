#include "CoinProp.h"

CoinProp::CoinProp()
{
	m_timerJump.setOneShot(true);
	m_timerJump.setWaitTime(m_intervalJump);
	m_timerJump.setOnTimeout([&]() { m_isJumping = false; });

	m_timerDisappear.setOneShot(true);
	m_timerDisappear.setWaitTime(m_intervalDisappear);
	m_timerDisappear.setOnTimeout([&]() { m_isValid = false; });

	m_velocity.m_x = (rand() % 2 ? 1 : -1) * 2 * SIZE_TILE;
	m_velocity.m_y = -3 * SIZE_TILE;
}

void CoinProp::setPosition(const TwoVector& position)
{
	this->m_position = position;
}

const TwoVector& CoinProp::getPosition() const
{
	return m_position;
}

const TwoVector& CoinProp::getSize() const
{
	return m_size;
}

void CoinProp::makeInvalid()
{
	m_isValid = false;
}

bool CoinProp::canRemove()
{
	return !m_isValid;
}

void CoinProp::onUpdate(double delta)
{
	m_timerJump.onUpdate(delta);
	m_timerDisappear.onUpdate(delta);

	if (m_isJumping)
	{
		m_velocity.m_y += m_gravity * delta;
	}
	else
	{
		m_velocity.m_x = 0;
		m_velocity.m_y = sin(SDL_GetTicks64() / 1000.0 * 4) * 30;
	}

	m_position += m_velocity * delta;
}

void CoinProp::onRender(SDL_Renderer* renderer)
{
	static SDL_Rect rect = { 0, 0, (int)m_size.m_x, (int)m_size.m_y };
	static SDL_Texture* texCoin = ResourcesManager::instance()->getTexturePool().find(ResID::Tex_Coin)->second;

	rect.x = (int)(m_position.m_x - m_size.m_x / 2);
	rect.y = (int)(m_position.m_y - m_size.m_y / 2);

	SDL_RenderCopy(renderer, texCoin, nullptr, &rect);
}