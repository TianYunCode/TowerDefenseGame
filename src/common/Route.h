#pragma once

#include "Tile.h"

#include <SDL.h>
#include <vector>

/**
* 路线类
*/
class Route
{
public:
	typedef std::vector<SDL_Point> IdxList;

public:
	Route() = default;

	/**
	* 构造一条路线
	* map 瓦片地图
	* idxOrigin 路线开始的点位
	*/
	Route(const TileMap& map, const SDL_Point& idxOrigin);
	~Route() = default;

	const IdxList& getIdxList() const;

private:
	IdxList m_idxList;

private:
	/**
	* 判断是否重复走过同一个瓦片
	* targetIdx 需要判断的瓦片点位
	*/
	bool checkDuplicateIdx(const SDL_Point& targetIdx);
};
