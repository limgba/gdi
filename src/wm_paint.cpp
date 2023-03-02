#include "../../framework.h"
#include "../../WindowsProject1.h"
#include "wm_paint.h"
#include "clipboard.h"
#include "shape.h"
#include "hdcmgr/hdcmgr.h"
#include "image/bitmapimage.h"
#include "image/imagebase.h"
#include "image/imageimpl.h"
#include "animation/animationmgr.h"
#include "animation/animation.h"
#include "obj/objmgr.h"
#include "obj/controlobjmgr.h"
#include "obj/rigidbodymgr.h"
#include "obj/objimpl/scene.h"
#include "obj/objimpl/actor.h"
#include "obj/objimpl/skill.h"
#include <winuser.h>
#include <string>

#define TIMER_ID_1 1

void OnDestroy(HWND hWnd)
{
	OnKillTimer(hWnd);
	DeleteDCAndBitMapAndImage();
}

void MyPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HDC hdc, PAINTSTRUCT* ps)
{
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	HdcMgr::Instance().CreateDCAndBitMap(hdc, cx, cy);

	if (0 == AnimationMgr::Instance().AnimationSize())
	{
		{
			std::wstring path = IMAGE_PATH_HEAD + L"background/ndmz.bmp";
			BitMapImage* bmp = new BitMapImage(path.c_str());

			ImageBase* image = new ImageBase();
			image->SetBitMapImage(bmp);
			image->SetIntervalMs(0);
			image->SetNextIndex(0);

			Animation* animation = new Animation();
			animation->InitClock();
			animation->SetLayer(0.0);
			animation->PushImageBase(image);
			AnimationMgr::Instance().PushAnimation(animation);

			Obj* obj = new Scene();
			obj->SetAnimation(animation);
			animation->SetObj(obj);
			ObjMgr::Instance().AddObj(obj);
		}

		{
			{
				int i = 0;
				std::wstring path = IMAGE_PATH_HEAD + L"picture/jiantou" + std::to_wstring(i) + L".bmp";
				BitMapImage* bmp = new BitMapImage(path.c_str());

				std::wstring mask_path = IMAGE_PATH_HEAD + L"mask/jiantou" + std::to_wstring(i) + L".bmp";
				BitMapImage* mask_bmp = new BitMapImage(mask_path.c_str());

				ImageImpl* image = new ImageImpl();
				image->SetBitMapImage(bmp);
				image->SetMaskBitMapImage(mask_bmp);
				image->SetIntervalMs(0);
				image->SetNextIndex(0);

				Animation* animation = new Animation();
				animation->InitClock();
				animation->SetLayer(1.0);
				animation->PushImageBase(image);

				AnimationMgr::Instance().PushAnimation(animation);

				Obj* obj = new Actor();
				obj->SetIsRigidbody(true);
				obj->SetAnimation(animation);
				animation->SetObj(obj);
				ObjMgr::Instance().AddObj(obj);
				ControlObjMgr::Instance().PushControlObj(obj);
			}

			{
				int i = 1;
				std::wstring path = IMAGE_PATH_HEAD + L"picture/jiantou" + std::to_wstring(i) + L".bmp";
				BitMapImage* bmp = new BitMapImage(path.c_str());

				std::wstring mask_path = IMAGE_PATH_HEAD + L"mask/jiantou" + std::to_wstring(i) + L".bmp";
				BitMapImage* mask_bmp = new BitMapImage(mask_path.c_str());

				ImageImpl* image = new ImageImpl();
				image->SetBitMapImage(bmp);
				image->SetMaskBitMapImage(mask_bmp);
				image->SetIntervalMs(0);
				image->SetNextIndex(0);

				Animation* animation = new Animation();
				animation->InitClock();
				animation->SetLayer(2.0);
				animation->PushImageBase(image);

				AnimationMgr::Instance().PushAnimation(animation);

				Obj* obj = new Skill();
				obj->SetAnimation(animation);
				obj->SetCoordinate(200, 200);
				obj->SetIsRigidbody(true);
				animation->SetObj(obj);
				ObjMgr::Instance().AddObj(obj);
			}

			{
				Animation* animation = new Animation();
				animation->InitClock();
				animation->SetLayer(2.0);
				for (int i = 0; i < 7; ++i)
				{
					std::wstring path = IMAGE_PATH_HEAD + L"picture/xiaojiantou" + std::to_wstring(i) + L".bmp";
					BitMapImage* bmp = new BitMapImage(path.c_str());

					std::wstring mask_path = IMAGE_PATH_HEAD + L"mask/xiaojiantou" + std::to_wstring(i) + L".bmp";
					BitMapImage* mask_bmp = new BitMapImage(mask_path.c_str());

					ImageImpl* image = new ImageImpl();
					image->SetBitMapImage(bmp);
					image->SetMaskBitMapImage(mask_bmp);
					image->SetIntervalMs(1000 + i * 1000);
					image->SetNextIndex(i + 1);
					animation->PushImageBase(image);
				}
				AnimationMgr::Instance().PushAnimation(animation);

				Obj* obj = new Skill();
				obj->SetAnimation(animation);
				obj->SetCoordinate(400, 300);
				obj->SetIsRigidbody(true);
				obj->m_obj_type = 1;
				animation->SetObj(obj);
				ObjMgr::Instance().AddObj(obj);
			}
		}

		AnimationMgr::Instance().DirtyLayer();
	}

	RigidBodyMgr::Instance().CollisionCheck();
	AnimationMgr::Instance().Play();

	BitBlt(hdc, 0, 0, cx, cy, HdcMgr::Instance().GetHdc1(), 0, 0, SRCCOPY);
}

void OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	int add = 10;
	switch (wParam)
	{
	case 'W':
	{
		ControlObjMgr::Instance().ChangeObjCoordinate(0, -add);
	}
	break;
	case 'A':
	{
		ControlObjMgr::Instance().ChangeObjCoordinate(-add, 0);
	}
	break;
	case 'S':
	{
		ControlObjMgr::Instance().ChangeObjCoordinate(0, add);
	}
	break;
	case 'D':
	{
		ControlObjMgr::Instance().ChangeObjCoordinate(add, 0);
	}
	break;
	}
}

void OnLeftButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//MessageBox(hWnd, TEXT("hhh"), TEXT("fff"), MB_OK | MB_ICONINFORMATION);
	//code for saving bitmap
	return;
	//if (::OpenClipboard(NULL))
	//{
	//	HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP); //’‚“ªæ‰∑µªÿNULL
	//	HDC hdc = GetDC(NULL);
	//	PBITMAPINFO pBitmapInfo = CreateBitmapInfoStruct(hBitmap);
	//	CreateBMPFile((LPTSTR)_T("c:\\temp\\picture.bmp"), pBitmapInfo, hBitmap, hdc);
	//	ReleaseDC(NULL, hdc);
	//}
	//::CloseClipboard();
}

void OnRightButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	ControlObjMgr::Instance().ChangeObjCoordinate(10, 10);
}

void DeleteDCAndBitMapAndImage()
{
	AnimationMgr::Instance().DeleteAllAnimation();
	ObjMgr::Instance().DeleteAllObj();
	HdcMgr::Instance().DeleteDCAndBitMap();
}

void OnSetTimer(HWND hWnd)
{
	SetTimer(hWnd, TIMER_ID_1, 55, nullptr);
}

void OnKillTimer(HWND hWnd)
{
	KillTimer(hWnd, TIMER_ID_1);
}

void OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case TIMER_ID_1:
	{
		OnTimer_1(hWnd, lParam);
	}
	break;
	}
}

void OnTimer_1(HWND hWnd, LPARAM lParam)
{
	InvalidateRect(hWnd, NULL, false);
}

