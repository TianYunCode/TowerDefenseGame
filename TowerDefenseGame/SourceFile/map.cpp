#include "../HeaderFile/map.h"

bool Map::load(const string& path)
{
	ifstream file(path);
	if (!file.good()) return false;

	TileMap tile_map_temp;

	int idx_x = -1, idx_y = -1;

	string str_line;
	while (getline(file, str_line))
	{
		str_line = trim_str(str_line);
		if (str_line.empty()) continue;

		idx_x = -1, idx_y++;
		tile_map_temp.emplace_back();

		string str_tile;
		stringstream str_stream(str_line);
		while (getline(str_stream, str_tile, ','))
		{
			idx_x++;
			tile_map_temp[idx_y].emplace_back();
			Tile& tile = tile_map_temp[idx_y].back();
			load_tile_from_string(tile, str_tile);
		}
	}

	file.close();

	if (tile_map_temp.empty() || tile_map_temp[0].empty()) return false;

	tile_map = tile_map_temp;

	generate_map_cache();

	return true;
}

size_t Map::get_width() const
{
	if (tile_map.empty()) return 0;

	return tile_map[0].size();
}

size_t Map::get_height() const
{
	return tile_map.size();
}

const TileMap& Map::get_tile_map() const
{
	return tile_map;
}

const SDL_Point& Map::get_idx_home() const
{
	return idx_home;
}

const Map::SpawnerRoutePool& Map::get_idx_spawner_pool() const
{
	return spwaner_route_pool;
}

void Map::place_tower(const SDL_Point& idx_tile)
{
	tile_map[idx_tile.y][idx_tile.x].has_tower = true;
}

string Map::trim_str(const string& str)
{
	size_t begin_idx = str.find_first_not_of(" \t"); //定位到不是空格的位置（字符串头部）
	if (begin_idx == string::npos) return ""; //找不到非空格的位置（str是空字符串或全空格字符串）
	size_t end_idx = str.find_last_not_of(" \t"); //定位到不是空格的位置（字符串尾部）
	size_t idx_range = end_idx - begin_idx + 1;

	return str.substr(begin_idx, idx_range);
}

void Map::load_tile_from_string(Tile& tile, const string& str)
{
	string str_tidy = trim_str(str);

	string str_value;
	vector<int> values;
	stringstream str_stream(str_tidy);

	while (getline(str_stream, str_value, '\\'))
	{
		int value;
		try
		{
			value = stoi(str_value);
		}
		catch (const invalid_argument&)
		{
			value = -1;
		}
		values.push_back(value);
	}

	tile.terrian = (values.size() < 1 || values[0] < 0) ? 0 : values[0];
	tile.decoration = (values.size() < 2) ? -1 : values[1];
	tile.direction = (Tile::Direction)((values.size() < 3 || values[2] < 0) ? 0 : values[2]);
	tile.special_flag = (values.size() <= 3) ? -1 : values[3];
}

void Map::generate_map_cache()
{
	for (int y = 0; y < get_height(); y++)
	{
		for (int x = 0; x < get_width(); x++)
		{
			const Tile& tile = tile_map[y][x];
			if (tile.special_flag < 0) continue;

			if (tile.special_flag == 0)
			{
				idx_home.x = x;
				idx_home.y = y;
			}
			else
			{
				spwaner_route_pool[tile.special_flag] = Route(tile_map, { x, y });
			}
		}
	}
}