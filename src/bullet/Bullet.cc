#include "Bullet.h"

void Bullet::setVelocity(const TwoVector& velocity)
{
	this->m_velocity = velocity;

	if (m_canRotated)
	{
		double randian = std::atan2(velocity.m_y, velocity.m_x);
		m_angleAnimRotated = randian * 180 / 3.14159265;
	}
}

void Bullet::setPosition(const TwoVector& position)
{
	this->m_position = position;
}

void Bullet::setDamage(double damage)
{
	this->m_damage = damage;
}

const TwoVector& Bullet::getSize() const
{
	return m_size;
}

const TwoVector& Bullet::getPosition() const
{
	return m_position;
}

double Bullet::getDamage() const
{
	return m_damage;
}

double Bullet::getDamageRange() const
{
	return m_damageRange;
}

void Bullet::disableCollide()
{
	m_isCollisional = false;
}

bool Bullet::canCollide() const
{
	return m_isCollisional;
}

void Bullet::makeInvalid()
{
	m_isValid = false;
	m_isCollisional = false;
}

bool Bullet::canRemove() const
{
	return !m_isValid;
}

void Bullet::onUpdate(double delta)
{
	m_animation.onUpdate(delta);
	m_position += m_velocity * delta;

	static const SDL_Rect& rectMap = ConfigManager::instance()->m_rectTileMap;

	if (m_position.m_x - m_size.m_x / 2 <= rectMap.x ||
		m_position.m_x + m_size.m_x / 2 >= rectMap.x + rectMap.w ||
		m_position.m_y - m_size.m_y / 2 <= rectMap.y ||
		m_position.m_y + m_size.m_y / 2 >= rectMap.y + rectMap.h)
	{
		m_isValid = false;
	}
}

void Bullet::onRender(SDL_Renderer* renderer)
{
	static SDL_Point point;

	point.x = (int)(m_position.m_x - m_size.m_x / 2);
	point.y = (int)(m_position.m_y - m_size.m_y / 2);

	m_animation.onRender(renderer, point, m_angleAnimRotated);
}

void Bullet::onCollide(Enemy* enemy)
{
	m_isValid = false;
	m_isCollisional = false;
}
