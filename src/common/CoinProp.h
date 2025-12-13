#pragma once

#include "Tile.h"
#include "Timer.h"
#include "TwoVector.h"
#include "ResourcesManager.h"

#include <SDL.h>

class CoinProp
{
public:
	CoinProp();
	~CoinProp() = default;

	void setPosition(const TwoVector& position);

	const TwoVector& getPosition() const;
	const TwoVector& getSize() const;

	void makeInvalid();
	bool canRemove();

	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

private:
	TwoVector m_position;
	TwoVector m_velocity;

	Timer m_timerJump;
	Timer m_timerDisappear;

	bool m_isValid = true;
	bool m_isJumping = true;

	double m_gravity = 490;
	double m_intervalJump = 0.75;
	TwoVector m_size = { 16, 16 };
	double m_intervalDisappear = 10;
};
