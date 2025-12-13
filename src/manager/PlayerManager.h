#pragma once

#include "Tile.h"
#include "Facing.h"
#include "TwoVector.h"
#include "Manager.h"
#include "Animation.h"
#include "CoinManager.h"
#include "EnemyManager.h"
#include "ResourcesManager.h"

#include <SDL.h>

class PlayerManager : public Manager<PlayerManager>
{
	friend class Manager<PlayerManager>;

public:
	void onInput(const SDL_Event& event);
	void onUpdate(double delta);
	void onRender(SDL_Renderer* renderer);

	double getCurrentMp() const;

protected:
	PlayerManager();
	~PlayerManager() = default;

private:
	TwoVector m_size;
	TwoVector m_position;
	TwoVector m_velocity;

	SDL_Rect m_rectHitboxFlash = { 0 };
	SDL_Rect m_rectHitboxImpact = { 0 };

	double m_mp = 100;

	double m_speed = 0;

	bool m_canReleaseFlash = true;
	bool m_isReleasingFlash = false;
	bool m_isReleasingImpact = false;

	bool m_isMoveUp = false;
	bool m_isMoveDown = false;
	bool m_isMoveLeft = false;
	bool m_isMoveRight = false;

	Animation m_animIdleUp;
	Animation m_animIdleDown;
	Animation m_animIdleLeft;
	Animation m_animIdleRight;
	Animation m_animAttackUp;
	Animation m_animAttackDown;
	Animation m_animAttackLeft;
	Animation m_animAttackRight;
	Animation* m_animCurrent = &m_animIdleRight;

	Animation m_animEffectFlashUp;
	Animation m_animEffectFlashDown;
	Animation m_animEffectFlashLeft;
	Animation m_animEffectFlashRight;
	Animation* m_animEffectFlashCurrent = nullptr;

	Animation m_animEffectImpactUp;
	Animation m_animEffectImpactDown;
	Animation m_animEffectImpactLeft;
	Animation m_animEffectImpactRight;
	Animation* m_animEffectImpactCurrent = nullptr;

	Timer m_timerReleaseFlashCd;
	Timer m_timerAutoIncreaseMp;

	Facing m_facing = Facing::Left;

private:
	void onReleaseFlash();
	void onReleaseImpact();
};
