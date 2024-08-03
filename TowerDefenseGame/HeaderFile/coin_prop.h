#ifndef _COIN_PROP_H_
#define _COIN_PROP_H_

#include "tile.h"
#include "timer.h"
#include "two_vector.h"
#include "resources_manager.h"

#include <SDL.h>

class CoinProp
{
public:
	CoinProp();
	~CoinProp() = default;

	void set_position(const TwoVector& position);
	const TwoVector& get_position() const;
	const TwoVector& get_size() const;

	void make_invalid();
	bool can_remove();

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

private:
	TwoVector position;
	TwoVector velocity;

	Timer timer_jump;
	Timer timer_disappear;

	bool is_valid = true;
	bool is_jumping = true;

	double gravity = 490;
	double interval_jump = 0.75;
	TwoVector size = { 16, 16 };
	double interval_disappear = 10;
};

#endif