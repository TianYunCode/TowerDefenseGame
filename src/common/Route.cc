#include "Route.h"

Route::Route(const TileMap& map, const SDL_Point& idxOrigin)
{
	size_t widthMap = map[0].size();
	size_t heightMap = map.size();
	SDL_Point idxNext = idxOrigin;

	while (true)
	{
		if (idxNext.x >= widthMap || idxNext.y >= heightMap)
		{
			break;
		}

		if (checkDuplicateIdx(idxNext))
		{
			break;
		}
		else
		{
			m_idxList.push_back(idxNext);
		}

		bool isNextDirExist = true;
		const Tile& tile = map[idxNext.y][idxNext.x];

		if (tile.m_specialFlag == 0)
		{
			break;
		}

		switch (tile.m_direction)
		{
		case Tile::Direction::Up:
			idxNext.y--;
			break;
		case Tile::Direction::Down:
			idxNext.y++;
			break;
		case Tile::Direction::Left:
			idxNext.x--;
			break;
		case Tile::Direction::Right:
			idxNext.x++;
			break;
		default:
			isNextDirExist = false;
			break;
		}

		if (!isNextDirExist)
		{
			break;
		}
	}
}

const Route::IdxList& Route::getIdxList() const
{
	return m_idxList;
}

bool Route::checkDuplicateIdx(const SDL_Point& targetIdx)
{
	for (const SDL_Point& idx : m_idxList)
	{
		if (idx.x == targetIdx.x && idx.y == targetIdx.y)
		{
			return true;
		}
	}

	return false;
}