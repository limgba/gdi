#include "hdcmgr.h"

HdcMgr& HdcMgr::Instance()
{
	static HdcMgr hdc_mgr;
	return hdc_mgr;
}

HdcMgr::HdcMgr()
{
	m_hdc1 = nullptr;
	m_hcbmp1 = nullptr;
	m_old_bmp1 = nullptr;

	m_hdc2 = nullptr;
	m_hcbmp2 = nullptr;
	m_old_bmp2 = nullptr;
}

HdcMgr::~HdcMgr()
{
	this->DeleteDCAndBitMap();
}

void HdcMgr::CreateDCAndBitMap(HDC hdc, int cx, int cy)
{
	if (nullptr != m_hdc1)
	{
		return;
	}
	m_hdc1 = CreateCompatibleDC(hdc);
	m_hcbmp1 = CreateCompatibleBitmap(hdc, cx, cy);
	m_old_bmp1 = (HBITMAP)SelectObject(m_hdc1, m_hcbmp1);
	m_hdc2 = CreateCompatibleDC(hdc);
	m_hcbmp2 = CreateCompatibleBitmap(hdc, cx, cy);
	m_old_bmp2 = (HBITMAP)SelectObject(m_hdc2, m_hcbmp2);
}

void HdcMgr::DeleteDCAndBitMap()
{
	SelectObject(m_hdc2, m_old_bmp2);
	DeleteObject(m_hcbmp2);
	DeleteObject(m_hdc2);

	SelectObject(m_hdc1, m_old_bmp1);
	DeleteObject(m_hcbmp1);
	DeleteObject(m_hdc1);
}

HDC HdcMgr::GetHdc1()
{
	return m_hdc1;
}

HDC HdcMgr::GetHdc2()
{
	return m_hdc2;
}
