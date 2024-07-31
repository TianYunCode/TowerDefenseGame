#ifndef _MAP_H_
#define _MAP_H_

#include "tile.h"
#include "route.h"

#include <SDL.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

//地图类
class Map
{
public:
	//刷怪点的路径池 每个刷怪点都有自己的行进路径
	typedef unordered_map<int, Route> SpawnerRoutePool;

public:
	Map() = default;
	~Map() = default;

	bool load(const string& path);	//加载地图文件
	
	size_t get_width() const;
	size_t get_height() const;

	const TileMap& get_tile_map() const;
	const SDL_Point& get_idx_home() const;
	const SpawnerRoutePool& get_idx_spawner_pool() const;

	void place_tower(const SDL_Point& idx_tile); //放置防御塔

private:
	TileMap tile_map;	//瓦片数组
	SDL_Point idx_home = { 0 };
	SpawnerRoutePool spwaner_route_pool;

private:
	string trim_str(const string& str);//清除字符串的首尾空格
	void load_tile_from_string(Tile& tile, const string& str);
	void generate_map_cache();
};

#endif