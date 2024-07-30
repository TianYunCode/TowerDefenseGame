#ifndef _BANNER_H_
#define _BANNER_H_

#include "../tower/timer.h"
#include "../vector2.h"
#include "../manager/config_manager.h"
#include "../manager/resources_manager.h"

#include <SDL.h>

class Banner
{
public:
	Banner();
	~Banner() = default;

	void set_center_position(const Vector2& pos);

	void on_update(double delta);
	void on_render(SDL_Renderer* renderer);

	bool check_end_dispaly();

private:
	Vector2 pos_center;

	Vector2 size_foreground;
	Vector2 size_background;

	SDL_Texture* tex_foreground = nullptr;
	SDL_Texture* tex_background = nullptr;

	Timer timer_display;
	bool is_end_display = false;
};

#endif
