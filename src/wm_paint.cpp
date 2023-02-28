#include "../../framework.h"
#include "../../WindowsProject1.h"
#include "hdcmgr/hdcmgr.h"
#include "image/bitmapimage.h"
#include "obj/objimpl/scene.h"
#include "obj/objimpl/actor.h"
#include "obj/controlobjmgr.h"
#include "obj/rigidbodymgr.h"
#include "obj/objmgr.h"
#include "animation/animationmgr.h"
#include "animation/animation.h"
#include "wm_paint.h"
#include "shape.h"
#include <winuser.h>
#include <string>
#include "image/imagebase.h"
#include "image/imageimpl.h"

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

			Scene* scene = new Scene();
			scene->SetAnimation(animation);
			animation->SetObj(scene);
			ObjMgr::Instance().AddObj(scene);
		}

		{
			Animation* animation = new Animation();
			animation->InitClock();
			animation->SetLayer(0.0);
			for (int i = 0; i < 2; ++i)
			{
				std::wstring path = IMAGE_PATH_HEAD + L"picture/jiantou" + std::to_wstring(i) + L".bmp";
				BitMapImage* bmp = new BitMapImage(path.c_str());

				std::wstring mask_path = IMAGE_PATH_HEAD + L"mask/jiantou" + std::to_wstring(i) + L".bmp";
				BitMapImage* mask_bmp = new BitMapImage(mask_path.c_str());

				ImageImpl* image = new ImageImpl();
				image->SetBitMapImage(bmp);
				image->SetMaskBitMapImage(mask_bmp);
				image->SetIntervalMs(0);
				image->SetNextIndex(0);
				animation->PushImageBase(image);
			}

			AnimationMgr::Instance().PushAnimation(animation);

			Actor* actor = new Actor();
			actor->SetIsRigidbody(true);
			actor->SetAnimation(animation);
			animation->SetObj(actor);
			ObjMgr::Instance().AddObj(actor);
			ControlObjMgr::Instance().PushControlObj(actor);
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

void OnRightButtonDown(WPARAM wParam, LPARAM lParam)
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
