#ifndef _MAP_H_
#define _MAP_H_

#include "tile.h"
#include "route.h"

#include <SDL.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

//��ͼ��
class Map
{
public:
	//ˢ�ֵ��·���� ÿ��ˢ�ֵ㶼���Լ����н�·��
	typedef unordered_map<int, Route> SpawnerRoutePool;

public:
	Map() = default;
	~Map() = default;

	bool load(const string& path);	//���ص�ͼ�ļ�
	
	size_t get_width() const;
	size_t get_height() const;

	const TileMap& get_tile_map() const;
	const SDL_Point& get_idx_home() const;
	const SpawnerRoutePool& get_idx_spawner_pool() const;

	void place_tower(const SDL_Point& idx_tile); //���÷�����

private:
	TileMap tile_map;	//��Ƭ����
	SDL_Point idx_home = { 0 };
	SpawnerRoutePool spwaner_route_pool;

private:
	string trim_str(const string& str);//����ַ�������β�ո�
	void load_tile_from_string(Tile& tile, const string& str);
	void generate_map_cache();
};

#endif