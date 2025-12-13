#pragma once

#include "Timer.h"
#include "Route.h"
#include "TwoVector.h"
#include "Animation.h"
#include "ConfigManager.h"

#include <functional>

class Enemy
{
public:
	typedef std::function<void(Enemy* enemy)> SkillCallback;

public:
	Enemy();
	~Enemy() = default;

	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

	void setOnSkillReleased(SkillCallback onSkillReleased);
	void increaseHp(double val);
	void decreaseHp(double val);
	void slowDown();

	void setPosition(const TwoVector& position);
	void setRoute(const Route* route);

	void makeInvalid();

	double getHp() const;
	const TwoVector& getSize() const;
	const TwoVector& getPosition() const;
	const TwoVector& getVelocity() const;
	double getDamage() const;
	double getRewardRatio() const;
	double getRecoverRadius() const;
	double getRecoverIntensity() const;

	bool canRemove() const;
	double getRouteProcess() const;

protected:
	TwoVector m_size;

	Timer m_timerSkill;

	Animation m_animUp;
	Animation m_animDown;
	Animation m_animLeft;
	Animation m_animRight;
	Animation m_animUpSketch;
	Animation m_animDownSketch;
	Animation m_animLeftSketch;
	Animation m_animRightSketch;

	double m_hp = 0;
	double m_maxHp = 0;
	double m_speed = 0;
	double m_maxSpeed = 0;
	double m_damage = 0;
	double m_rewardRatio = 0;
	double m_recoverInterval = 0;
	double m_recoverRange = 0;
	double m_recoverIntensity = 0;

private:
	TwoVector m_position;
	TwoVector m_velocity;
	TwoVector m_direction;

	bool m_isValid = true;

	Timer m_timerSketch;
	bool m_isShowSketch = false;

	Animation* m_animCurrent = nullptr;

	SkillCallback m_onSkillReleased;

	Timer m_timerRestoreSpeed;

	const Route* m_route = nullptr;
	int m_idxTarget = 0;
	TwoVector m_positionTarget;

private:
	void refreshPositionTarget();
};
