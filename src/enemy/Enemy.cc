#include "Enemy.h"

Enemy::Enemy()
{
	m_timerSkill.setOneShot(false);
	m_timerSkill.setOnTimeout([&]() { m_onSkillReleased(this); });

	m_timerSketch.setOneShot(true);
	m_timerSketch.setWaitTime(0.075);
	m_timerSketch.setOnTimeout([&]() { m_isShowSketch = false; });

	m_timerRestoreSpeed.setOneShot(true);
	m_timerRestoreSpeed.setOnTimeout([&]() { m_speed = m_maxSpeed; });
}

void Enemy::onUpdate(double delta)
{
	m_timerSkill.onUpdate(delta);
	m_timerSketch.onUpdate(delta);
	m_timerRestoreSpeed.onUpdate(delta);

	TwoVector moveDistance = m_velocity * delta;
	TwoVector targetDistance = m_positionTarget - m_position;
	m_position += moveDistance < targetDistance ? moveDistance : targetDistance;

	if (targetDistance.approxZero())
	{
		m_idxTarget++;
		refreshPositionTarget();

		m_direction = (m_positionTarget - m_position).normalize();
	}

	m_velocity.m_x = m_direction.m_x * m_speed * SIZE_TILE;
	m_velocity.m_y = m_direction.m_y * m_speed * SIZE_TILE;

	bool isShowXAmin = abs(m_velocity.m_x) >= abs(m_velocity.m_y);

	if (m_isShowSketch)
	{
		if (isShowXAmin)
		{
			m_animCurrent = m_velocity.m_x > 0 ? &m_animRightSketch : &m_animLeftSketch;
		}
		else
		{
			m_animCurrent = m_velocity.m_y > 0 ? &m_animDownSketch : &m_animUpSketch;
		}
	}
	else
	{
		if (isShowXAmin)
		{
			m_animCurrent = m_velocity.m_x > 0 ? &m_animRight : &m_animLeft;
		}
		else
		{
			m_animCurrent = m_velocity.m_y > 0 ? &m_animDown : &m_animUp;
		}
	}

	m_animCurrent->onUpdate(delta);
}

void Enemy::onRender(SDL_Renderer* renderer)
{
	static SDL_Rect rect;
	static SDL_Point point;
	static const int offsetY = 2;
	static const TwoVector sizeHpBar = { 40, 8 };
	static const SDL_Color colorBorder = { 116, 185, 124, 255 };
	static const SDL_Color colorContent = { 226, 255, 194, 255 };

	point.x = (int)(m_position.m_x - m_size.m_x / 2);
	point.y = (int)(m_position.m_y - m_size.m_y / 2);

	m_animCurrent->onRender(renderer, point);

	if (m_hp < m_maxHp)
	{
		rect.x = (int)(m_position.m_x - sizeHpBar.m_x / 2);
		rect.y = (int)(m_position.m_y - m_size.m_y / 2 - sizeHpBar.m_y - offsetY);
		rect.w = (int)(sizeHpBar.m_x * (m_hp / m_maxHp));
		rect.h = (int)sizeHpBar.m_y;
		SDL_SetRenderDrawColor(renderer, colorContent.r, colorContent.g, colorContent.b, colorContent.a);
		SDL_RenderFillRect(renderer, &rect);

		rect.w = (int)sizeHpBar.m_x;
		SDL_SetRenderDrawColor(renderer, colorBorder.r, colorBorder.g, colorBorder.b, colorBorder.a);
		SDL_RenderDrawRect(renderer, &rect);
	}
}

void Enemy::setOnSkillReleased(SkillCallback onSkillReleased)
{
	this->m_onSkillReleased = onSkillReleased;
}

void Enemy::increaseHp(double val)
{
	m_hp += val;

	if (m_hp > m_maxHp)
	{
		m_hp = m_maxHp;
	}
}

void Enemy::decreaseHp(double val)
{
	m_hp -= val;

	if (m_hp <= 0)
	{
		m_hp = 0;
		m_isValid = false;
	}

	m_isShowSketch = true;
	m_timerSketch.restart();
}

void Enemy::slowDown()
{
	m_speed = m_maxSpeed - 0.5;
	m_timerRestoreSpeed.setWaitTime(1);
	m_timerRestoreSpeed.restart();
}

void Enemy::setPosition(const TwoVector& position)
{
	this->m_position = position;
}

void Enemy::setRoute(const Route* route)
{
	this->m_route = route;

	refreshPositionTarget();
}

void Enemy::makeInvalid()
{
	m_isValid = false;
}

double Enemy::getHp() const
{
	return m_hp;
}

const TwoVector& Enemy::getSize() const
{
	return m_size;
}

const TwoVector& Enemy::getPosition() const
{
	return m_position;
}

const TwoVector& Enemy::getVelocity() const
{
	return m_velocity;
}

double Enemy::getDamage() const
{
	return m_damage;
}

double Enemy::getRewardRatio() const
{
	return m_rewardRatio;
}

double Enemy::getRecoverRadius() const
{
	return SIZE_TILE * m_recoverRange;
}

double Enemy::getRecoverIntensity() const
{
	return m_recoverIntensity;
}

bool Enemy::canRemove() const
{
	return !m_isValid;
}

double Enemy::getRouteProcess() const
{
	if (m_route->getIdxList().size() == 1)
	{
		return 1;
	}

	return (double)m_idxTarget / (m_route->getIdxList().size() - 1);
}

void Enemy::refreshPositionTarget()
{
	const Route::IdxList& idxList = m_route->getIdxList();

	if (m_idxTarget < idxList.size())
	{
		const SDL_Point& point = idxList[m_idxTarget];
		static const SDL_Rect& rectTileMap = ConfigManager::instance()->m_rectTileMap;

		m_positionTarget.m_x = rectTileMap.x + point.x * SIZE_TILE + SIZE_TILE / 2;
		m_positionTarget.m_y = rectTileMap.y + point.y * SIZE_TILE + SIZE_TILE / 2;
	}
}