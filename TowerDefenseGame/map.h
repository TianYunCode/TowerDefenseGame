#ifndef _MAP_H_
#define _MAP_H_

#include "tile.h"
#include "route.h"

#include <SDL.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Map
{
public:
	typedef std::unordered_map<int, Route> SpawnerRoutePool;

public:
	Map() = default;
	~Map() = default;

	bool load(const std::string& path);
	
	size_t get_width() const;
	size_t get_height() const;

	const TileMap& get_tile_map() const;
	const SDL_Point& get_idx_home() const;
	const SpawnerRoutePool& get_idx_spawner_pool() const;

	void place_tower(const SDL_Point& idx_tile);

private:
	TileMap tile_map;
	SDL_Point idx_home = { 0 };
	SpawnerRoutePool spwaner_route_pool;

private:
	std::string trim_str(const std::string& str);
	void load_tile_from_string(Tile& tile, const std::string& str);
	void generate_map_cache();
};

#endif
