#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

using namespace std;

//瓦片尺寸
#define SIZE_TILE 48

//瓦片结构体
struct Tile
{
	//方向枚举
	enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right
	};

	int terrian = 0;		//地形瓦片
	int decoration = -1;	//装饰瓦片
	Direction direction = Direction::None; //行进路线
	int special_flag = -1;	//特殊标志
	bool has_tower = false; //塔标志，用于判断当前瓦片有没有放置防御塔
};

//二维数组，用于表示地图
typedef vector<vector<Tile>> TileMap;

#endif