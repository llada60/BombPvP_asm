/******************************************************************* 
 *  Copyright: Turing Team
 *  All rights reserved. 
 *
 *  �ļ�����: CHelpScene.h
 *  ��Ҫ����: ����������,��ʾ��Ϸ˵����Ϣ
 *
 *  ����: ���³�
 *  ��������: 2017��6��3��
 *  ˵��:
 *
 *  �޸�����:
 *  ����:
 *  ˵��:
 *  ��ǰ�汾: 1.0
 ******************************************************************/ 
#ifndef CHELPSCENE_H_
#define CHELPSCENE_H_

#include "Sys.h"

class CHelpScene
{
public:
	CHelpScene();
	~CHelpScene();
public:
	void HelpSceneInit(HINSTANCE hIns);
	void HelpSceneShow(HDC hdc);

	// �������λ�� �޸� m_isSelect ����Ƿ�����������ؿ�
	void MouseMove(POINT point);

	/* �������Ƿ������ڷ���ѡ���
	** true: ����ڷ��ؿ���
	** false: ���δ�ڷ��ؿ���
	*/
	bool m_isSelect;
private:
	HBITMAP m_bitmap_help;
	HBITMAP m_bitmap_return;
	HBITMAP m_bitmap_return_select;
};

#endif // !CHELPSCENE_H_

