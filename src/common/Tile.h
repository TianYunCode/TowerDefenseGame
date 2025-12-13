#pragma once

#include <vector>

#define SIZE_TILE 48

/**
* 瓦片类
*/
struct Tile
{
	// 方向枚举
	enum class Direction
	{
		None = 0,	// 无
		Up,			// 上
		Down,		// 下
		Left,		// 左
		Right		// 右
	};

	int m_terrian = 0;							// 第一层纹理
	int m_decoration = -1;						// 第二层纹理（装饰）
	int m_specialFlag = -1;						// 特殊标志（家、出生点）
	bool m_hasTower = false;					// 是否存在防御塔
	Direction m_direction = Direction::None;	// 方向
};

typedef std::vector<std::vector<Tile>> TileMap;
