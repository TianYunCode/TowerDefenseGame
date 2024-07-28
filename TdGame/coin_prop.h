#ifndef _COIN_PROP_H_
#define _COIN_PROP_H_

#include "tile.h"
#include "timer.h"
#include "vector2.h"
#include "resources_manager.h"

#include <SDL.h>

class CoinProp
{
public:
	CoinProp();
	~CoinProp() = default;

	void set_position(const Vector2& position);
	const Vector2& get_position() const;
	const Vector2& get_size() const;

	void make_invalid();
	bool can_remove();

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

private:
	Vector2 position;
	Vector2 velocity;

	Timer timer_jump;
	Timer timer_disappear;

	bool is_valid = true;
	bool is_jumping = true;

	double gravity = 490;
	double interval_jump = 0.75;
	Vector2 size = { 16, 16 };
	double interval_disappear = 10;
};

#endif
