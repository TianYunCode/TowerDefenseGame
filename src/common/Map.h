#pragma once

#include "Tile.h"
#include "Route.h"

#include <SDL.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

/**
* 地图类
*/
class Map
{
public:
	typedef std::unordered_map<int, Route> SpawnerRoutePool;

public:
	Map() = default;
	~Map() = default;

	/**
	* 从csv文件加载地图
	*/
	bool load(const std::string& path);
	
	size_t getWidth() const;
	size_t getHeight() const;

	const TileMap& getTileMap() const;
	const SDL_Point& getIdxHome() const;
	const SpawnerRoutePool& getIdxSpawnerPool() const;

	void placeTower(const SDL_Point& idxTile);

private:
	TileMap m_tileMap;						// 瓦片地图
	SDL_Point m_idxHome = { 0 };			// 家的点位
	SpawnerRoutePool m_spwanerRoutePool;	// 行进路线池

private:
	/**
	* 去除字符串左右两边的空白字符
	*/
	std::string trimStr(const std::string& str);

	// 从字符串加载出瓦片
	void loadTileFromString(Tile& tile, const std::string& str);

	// 生成地图缓存（家和路线）
	void generateMapCache();
};
