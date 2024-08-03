#ifndef _BANNER_H_
#define _BANNER_H_

#include "timer.h"
#include "two_vector.h"
#include "config_manager.h"
#include "resources_manager.h"

#include <SDL.h>

class Banner
{
public:
	Banner();
	~Banner() = default;

	void set_center_position(const TwoVector& pos);

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	bool check_end_dispaly();

private:
	TwoVector pos_center;

	TwoVector size_foreground;
	TwoVector size_background;

	SDL_Texture* tex_foreground = nullptr;
	SDL_Texture* tex_background = nullptr;

	Timer timer_display;
	bool is_end_display = false;
};

#endif