#include "Map.h"

bool Map::load(const std::string& path)
{
	std::ifstream file(path);
	if (!file.good())
	{
		return false;
	}

	TileMap tileMapTemp;

	int idxX = -1, idxY = -1;

	std::string strLine;
	while (std::getline(file, strLine))
	{
		strLine = trimStr(strLine);
		if (strLine.empty())
		{
			continue;
		}

		idxX = -1, idxY++;
		tileMapTemp.emplace_back();

		std::string strTile;
		std::stringstream strStream(strLine);
		while (std::getline(strStream, strTile, ','))
		{
			idxX++;
			tileMapTemp[idxY].emplace_back();
			Tile& tile = tileMapTemp[idxY].back();
			loadTileFromString(tile, strTile);
		}
	}

	file.close();

	if (tileMapTemp.empty() || tileMapTemp[0].empty())
	{
		return false;
	}

	m_tileMap = tileMapTemp;

	generateMapCache();

	return true;
}

size_t Map::getWidth() const
{
	if (m_tileMap.empty())
	{
		return 0;
	}

	return m_tileMap[0].size();
}

size_t Map::getHeight() const
{
	return m_tileMap.size();
}

const TileMap& Map::getTileMap() const
{
	return m_tileMap;
}

const SDL_Point& Map::getIdxHome() const
{
	return m_idxHome;
}

const Map::SpawnerRoutePool& Map::getIdxSpawnerPool() const
{
	return m_spwanerRoutePool;
}

void Map::placeTower(const SDL_Point& idxTile)
{
	m_tileMap[idxTile.y][idxTile.x].m_hasTower = true;
}

std::string Map::trimStr(const std::string& str)
{
	size_t beginIdx = str.find_first_not_of(" \t");
	if (beginIdx == std::string::npos)
	{
		return "";
	}

	size_t endIdx = str.find_last_not_of(" \t");
	size_t idxRange = endIdx - beginIdx + 1;

	return str.substr(beginIdx, idxRange);
}

void Map::loadTileFromString(Tile& tile, const std::string& str)
{
	std::string strTidy = trimStr(str);

	std::string strValue;
	std::vector<int> values;
	std::stringstream strStream(strTidy);

	while (std::getline(strStream, strValue, '\\'))
	{
		int value;
		try
		{
			value = std::stoi(strValue);
		}
		catch (const std::invalid_argument&)
		{
			value = -1;
		}
		values.push_back(value);
	}

	tile.m_terrian = (values.size() < 1 || values[0] < 0) ? 0 : values[0];
	tile.m_decoration = (values.size() < 2) ? -1 : values[1];
	tile.m_direction = (Tile::Direction)((values.size() < 3 || values[2] < 0) ? 0 : values[2]);
	tile.m_specialFlag = (values.size() <= 3) ? -1 : values[3];
}

void Map::generateMapCache()
{
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			const Tile& tile = m_tileMap[y][x];
			if (tile.m_specialFlag < 0)
			{
				continue;
			}

			if (tile.m_specialFlag == 0)
			{
				m_idxHome.x = x;
				m_idxHome.y = y;
			}
			else
			{
				m_spwanerRoutePool[tile.m_specialFlag] = Route(m_tileMap, { x, y });
			}
		}
	}
}