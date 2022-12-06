#ifndef CGMAEMAP_H_
#define CGMAEMAP_H_

#include "Sys.h"

#define MAP_WIDTH  15
#define MAP_HEIGHT 13

 // 地图上障碍物类型 与mapData中数据一一对应
enum MapType
{
	No, R_B_, Y_B_, Box, R_H_, Y_H_, B_H_, Tree, WIND, Popo,
};

class CGameMap
{
public:
	CGameMap();
	~CGameMap();

	void MapInit(HINSTANCE hIns);
	void MapShow(HDC hdc);
	void MapUpShow(HDC hdc);

	/* 泡泡爆炸 消除地图障碍物
	** i , j 对应数组下标 power 泡泡威力 可在单一方向消除几块障碍物
	*/
	void MapBlast(int i, int j, int power);

	void BlastBlock_One(int i, int j);   // 炸第一格障碍物
	void BlastBlock_Two(int i, int j);   // 炸第二格障碍物
	void BlastBlock_Three(int i, int j); // 炸第三格障碍物
	void BlastBlock_Four(int i, int j);  // 炸第四格障碍物
public:
	int map_type[MAP_HEIGHT][MAP_WIDTH];
	int m_nShowID;                       // 风车转动切换图片记录ID
private:
	HBITMAP m_bitmap_redBrick;
	HBITMAP m_bitmap_redHouse;
	HBITMAP m_bitmap_yellowBrick;
	HBITMAP m_bitmap_yellowHouse;
	HBITMAP m_bitmap_Tree;
	HBITMAP m_bitmap_Box;
	HBITMAP m_bitmap_blueHouse;
	HBITMAP m_bitmap_windUp;
	HBITMAP m_bitmap_windDown;
	HBITMAP m_bitmap_ShadowBlock;
};

#endif // !CGMAEMAP_H_

