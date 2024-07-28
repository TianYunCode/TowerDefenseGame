#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "banner.h"
#include "manager.h"
#include "config_manager.h"
#include "enemy_manager.h"
#include "wave_manager.h"
#include "resources_manager.h"
#include "tower_manager.h"
#include "bullet_manager.h"
#include "status_bar.h"
#include "panel.h"
#include "place_panel.h"
#include "upgrade_panel.h"
#include "player_manager.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	int run(int argc, char** argv);

protected:
	GameManager();
	~GameManager();

private:
	SDL_Event event;
	bool is_quit = false;

	StatusBar status_bar;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_Texture* tex_tile_map = nullptr;

	Panel* place_panel = nullptr;
	Panel* upgrade_panel = nullptr;
	Banner* banner = nullptr;

private:
	void init_assert(bool flag, const char* err_msg);

	void on_input();
	void on_update(double delta);
	void on_render();

	bool generate_tile_map_texture();
	bool check_home(const SDL_Point& idx_tile_selected);
	bool get_cursor_idx_tile(SDL_Point& idx_tile_selected, int screen_x, int screen_y) const;
	bool can_place_tower(const SDL_Point& idx_tile_selected) const;
	void get_selected_tile_center_pos(SDL_Point& pos, const SDL_Point& idx_tile_selected) const;
};

#endif
