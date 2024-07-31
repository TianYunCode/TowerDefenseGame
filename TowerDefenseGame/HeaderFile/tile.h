#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

using namespace std;

//��Ƭ�ߴ�
#define SIZE_TILE 48

//��Ƭ�ṹ��
struct Tile
{
	//����ö��
	enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right
	};

	int terrian = 0;		//������Ƭ
	int decoration = -1;	//װ����Ƭ
	Direction direction = Direction::None; //�н�·��
	int special_flag = -1;	//�����־
	bool has_tower = false; //����־�������жϵ�ǰ��Ƭ��û�з��÷�����
};

//��ά���飬���ڱ�ʾ��ͼ
typedef vector<vector<Tile>> TileMap;

#endif