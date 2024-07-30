#ifndef _ROUTE_H_
#define _ROUTE_H_

#include "tile.h"

#include <SDL.h>
#include <vector>

//Â·¾¶Àà
class Route
{
public:
	typedef std::vector<SDL_Point> IdxList;

public:
	Route() = default;
	Route(const TileMap& map, const SDL_Point& idx_origin);
	~Route() = default;

	const IdxList& get_idx_list() const;

private:
	IdxList idx_list;

private:
	bool check_duplicate_idx(const SDL_Point& target_idx);
};

#endif