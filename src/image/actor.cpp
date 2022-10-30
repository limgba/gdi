#include "actor.h"
#include "../hdcmgr/hdcmgr.h"


Actor::Actor(LPCWSTR path, int x, int y)
	: BitMapImage(path, x, y)
{
}

Actor::~Actor()
{
	if (nullptr != m_hbitmap_mask)
	{
		DeleteObject(m_hbitmap_mask);
	}
}

void Actor::LoadBitMapImage(LPCWSTR path)
{
	BitMapImage::LoadBitMapImage(path);

	std::wstring mask_path(L"mask/");
	std::wstring wstr(path);
	wstr = wstr.substr(wstr.find_last_of('/'));
	wstr = wstr.substr(wstr.find_first_not_of('/'));
	mask_path += wstr;
	m_hbitmap_mask = (HBITMAP)LoadImage(NULL, mask_path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void Actor::SelectAndBitBlt() const
{
	HDC hdc1 = HdcMgr::Instance().GetHdc1();
	HDC hdc2 = HdcMgr::Instance().GetHdc2();

	if (nullptr != m_hbitmap_mask)
	{
		SelectObject(hdc2, m_hbitmap_mask);
		BitBlt(hdc1, m_x, m_y, m_cx, m_cy, hdc2, 0, 0, SRCAND);
	}

	if (nullptr != m_hbitmap)
	{
		SelectObject(hdc2, m_hbitmap);
		BitBlt(hdc1, m_x, m_y, m_cx, m_cy, hdc2, 0, 0, SRCPAINT);
	}
}

