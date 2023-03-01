#include "bitmapimage.h"
#include "../hdcmgr/hdcmgr.h"

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif


BitMapImage::BitMapImage(LPCWSTR path)
{
	m_path = path;
}

BitMapImage::~BitMapImage()
{
	if (nullptr != m_hbitmap)
	{
		DeleteObject(m_hbitmap);
	}
}

void BitMapImage::LoadBitMapImage()
{
	if (m_hbitmap != nullptr)
	{
		DeleteObject(m_hbitmap);
	}
	m_hbitmap = (HBITMAP)LoadImage(NULL, m_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bmp;
	GetObject(m_hbitmap, sizeof(BITMAP), &bmp);
	m_cx = bmp.bmWidth;
	m_cy = bmp.bmHeight;
}

void BitMapImage::SelectAndBitBlt(int x, int y, int operations) const
{
	HDC hdc1 = HdcMgr::Instance().GetHdc1();
	HDC hdc2 = HdcMgr::Instance().GetHdc2();

	SelectObject(hdc2, m_hbitmap);
	BitBlt(hdc1, x, y, m_cx, m_cy, hdc2, 0, 0, operations);
}

