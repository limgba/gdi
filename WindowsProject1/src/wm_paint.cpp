#include "../framework.h"
#include "../WindowsProject1.h"
#include "wm_paint.h"
#include "shape.h"
#include <winuser.h>
#include <string>

void MyPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HDC hdc, PAINTSTRUCT* ps)
{
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	RECT client_rect;
	GetClientRect(hWnd, &client_rect);

	HDC hdc1 = CreateCompatibleDC(hdc);
	HBITMAP hcbmp1 = CreateCompatibleBitmap(hdc, cx, cy);
	HBITMAP old_bmp1 = (HBITMAP)SelectObject(hdc1, hcbmp1);
	Rectangle(hdc1, -1, -1, cx, cy);

	HDC hdc2 = CreateCompatibleDC(hdc);
	HBITMAP hcbmp2 = CreateCompatibleBitmap(hdc, cx, cy);
	HBITMAP old_bmp2 = (HBITMAP)SelectObject(hdc2, hcbmp2);


	HBITMAP hbmp1 = (HBITMAP)LoadImage(NULL, L"c:\\temp\\picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hdc2, hbmp1);
	BitBlt(hdc1, 0, 0, cx / 2, cy / 2, hdc2, 0, 0, SRCCOPY);
	BITMAP bmp1;
	GetObject(hbmp1, sizeof(BITMAP), &bmp1);
	lmb::Rectangle rect1;
	rect1.left = rx;
	rect1.top = ry;
	rect1.right = rect1.left + bmp1.bmWidth;
	rect1.bottom = rect1.top + bmp1.bmHeight;


	HBITMAP hbmp2 = (HBITMAP)LoadImage(NULL, L"c:\\temp\\aa.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hdc2, hbmp2);
	BitBlt(hdc1, cx / 2, cy / 2, cx, cy, hdc2, 0, 0, SRCCOPY);
	BITMAP bmp2;
	GetObject(hbmp2, sizeof(BITMAP), &bmp2);
	lmb::Rectangle rect2;
	rect2.left = client_rect.right / 2;
	rect2.top = client_rect.bottom / 2;
	rect2.right = rect2.left + bmp2.bmWidth;
	rect2.bottom = rect2.top + bmp2.bmHeight;

	//if (!lmb::Intersect(rect1, rect2))
	{
	}
	Rectangle(hdc1, rx, ry, rx + 10, ry + 10);
	BitBlt(hdc, 0, 0, cx, cy, hdc1, 0, 0, SRCCOPY);

	DeleteObject(hbmp2);
	SelectObject(hdc2, old_bmp2);
	DeleteObject(hcbmp2);
	DeleteObject(hdc2);

	DeleteObject(hbmp1);
	SelectObject(hdc1, old_bmp1);
	DeleteObject(hcbmp1);
	DeleteObject(hdc1);

}