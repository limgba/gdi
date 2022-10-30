#include "../../framework.h"
#include "../../WindowsProject1.h"
#include "hdcmgr/hdcmgr.h"
#include "image/image.h"
#include "image/background.h"
#include "image/actor.h"
#include "image/imagemgr.h"
#include "wm_paint.h"
#include "shape.h"
#include <winuser.h>
#include <string>

void MyPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HDC hdc, PAINTSTRUCT* ps)
{
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	HdcMgr::Instance().CreateDCAndBitMap(hdc, cx, cy);

	if (0 == BitMapImageMgr::Instance().ImageCount())
	{
		{
			std::wstring path = IMAGE_PATH_HEAD + L"background/ndmz.bmp";
			BackGroundImage* bmp = new BackGroundImage(path.c_str(), 0, 0);
			bmp->SetIsRigidbody(false);
			bmp->SetObjType(BITMAP_IMAGE_OBJ_TYPE_BACK_GROUND);
			bmp->SetLayer(0.0);
			BitMapImageMgr::Instance().PushBitMapImage(bmp);
		}

		{
			std::wstring path = IMAGE_PATH_HEAD + L"picture/jiantou.bmp";
			Actor* bmp = new Actor(path.c_str(), 0, 0);
			bmp->SetIsRigidbody(true);
			bmp->SetObjType(BITMAP_IMAGE_OBJ_TYPE_PLAYER);
			bmp->SetLayer(1.0);
			BitMapImageMgr::Instance().PushBitMapImage(bmp);
		}

		{
			std::wstring path = IMAGE_PATH_HEAD + L"picture/jiantou.bmp";
			Actor* bmp = new Actor(path.c_str(), cx / 2, cy / 2);
			bmp->SetIsRigidbody(true);
			bmp->SetObjType(BITMAP_IMAGE_OBJ_TYPE_SKILL);
			bmp->SetLayer(2.0);
			BitMapImageMgr::Instance().PushBitMapImage(bmp);
		}
	}

	BitMapImageMgr::Instance().CollisionCheck();
	BitMapImageMgr::Instance().SelectAndBitBltAll();

	BitBlt(hdc, 0, 0, cx, cy, HdcMgr::Instance().GetHdc1(), 0, 0, SRCCOPY);
}

void OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	BitMapImage* image = BitMapImageMgr::Instance().GetBitMapImage(1);
	if (nullptr == image)
	{
		return;
	}
	int add = 10;
	switch (wParam)
	{
	case 'W':
	{
		image->SetCoordinate(image->x(), image->y() - add);
	}
	break;
	case 'A':
	{
		image->SetCoordinate(image->x() - add, image->y());
	}
	break;
	case 'S':
	{
		image->SetCoordinate(image->x(), image->y() + add);
	}
	break;
	case 'D':
	{
		image->SetCoordinate(image->x() + add, image->y());
	}
	break;
	}
}

void OnRightButtonDown(WPARAM wParam, LPARAM lParam)
{
	BitMapImage* image = BitMapImageMgr::Instance().GetBitMapImage(1);
	if (nullptr == image)
	{
		return;
	}
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	image->SetCoordinate(x, y);
}

void DeleteDCAndBitMapAndImage()
{
	BitMapImageMgr::Instance().DeleteAllBitMapImage();
	HdcMgr::Instance().DeleteDCAndBitMap();
}
