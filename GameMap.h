/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CGameMap.h
 *  ��Ҫ����: ��Ϸ��ͼ��
 *
 *  ����: 
 *  ��������: 2017��6��4��
 *  ˵��:
 *
 *  �޸�����:
 *  ����:
 *  ˵��:
 *  ��ǰ�汾: 1.0
 ******************************************************************/ 

#ifndef CGMAEMAP_H_
#define CGMAEMAP_H_

#include "Sys.h"

#define MAP_WIDTH  15
#define MAP_HEIGHT 13

// ��ͼ���ϰ������� ��mapData������һһ��Ӧ
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

	/* ���ݱ�ը ������ͼ�ϰ��� 
	** i , j ��Ӧ�����±� power �������� ���ڵ�һ�������������ϰ���
	*/
	void MapBlast(int i, int j, int power ,int *arr);
	
	void BlastBlock_One(int i, int j, int *arr);   // ը��һ���ϰ���
	void BlastBlock_Two(int i, int j, int *arr);   // ը�ڶ����ϰ���
	void BlastBlock_Three(int i, int j, int *arr); // ը�������ϰ���
	void BlastBlock_Four(int i, int j, int *arr);  // ը���ĸ��ϰ���
public:
	int map_type[MAP_HEIGHT][MAP_WIDTH];
	int m_nShowID;                       // �糵ת���л�ͼƬ��¼ID
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

