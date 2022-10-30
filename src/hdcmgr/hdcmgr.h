#pragma once
#include "../../../framework.h"

class HdcMgr
{
public:
	static HdcMgr& Instance();
	HdcMgr();
	~HdcMgr();

	void CreateDCAndBitMap(HDC hdc, int cx, int cy);
	void DeleteDCAndBitMap();
	HDC GetHdc1();
	HDC GetHdc2();

private:
	HDC m_hdc1;
	HBITMAP m_hcbmp1;
	HBITMAP m_old_bmp1;

	HDC m_hdc2;
	HBITMAP m_hcbmp2;
	HBITMAP m_old_bmp2;
};