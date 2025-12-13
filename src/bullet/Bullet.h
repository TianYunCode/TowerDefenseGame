#pragma once

#include "TwoVector.h"
#include "Enemy.h"
#include "Animation.h"
#include "ConfigManager.h"

class Bullet
{
public:
	Bullet() = default;
	~Bullet() = default;

	void setVelocity(const TwoVector& velocity);
	void setPosition(const TwoVector& position);
	void setDamage(double damage);

	const TwoVector& getSize() const;
	const TwoVector& getPosition() const;

	double getDamage() const;
	double getDamageRange() const;

	void disableCollide();
	bool canCollide() const;
	void makeInvalid();
	bool canRemove() const;

	virtual void onUpdate(double delta);
	virtual void onRender(SDL_Renderer* renderer);
	virtual void onCollide(Enemy* enemy);

protected:
	TwoVector m_size;
	TwoVector m_velocity;
	TwoVector m_position;

	Animation m_animation;
	bool m_canRotated = false;

	double m_damage = 0;
	double m_damageRange = -1;

private:
	bool m_isValid = true;
	bool m_isCollisional = true;
	double m_angleAnimRotated = 0;
};
