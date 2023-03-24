#include "actor.h"
#include "../../animation/animation.h"
#include "../../image/imagebase.h"
#include "../../image/bitmapimage.h"
#include "../obj.h"
#include "../controlobjmgr.h"

void Actor::OnImpact(Obj* obj)
{
	if (nullptr == obj)
	{
		return;
	}
	switch (obj->GetObjType())
	{
	case BITMAP_IMAGE_OBJ_TYPE_SKILL:
	{
		ControlObjMgr::Instance().SetObjCoordinate(0, 0);
	}
	break;
	case BITMAP_IMAGE_OBJ_TYPE_MONSTER:
	{
		BitMapImage* my_bitmap = this->GetAnimation()->GetImageBase()->GetBitMapImage();
		BitMapImage* obj_bitmap = obj->GetAnimation()->GetImageBase()->GetBitMapImage();
		if (nullptr == my_bitmap || nullptr == obj_bitmap)
		{
			return;
		}
		double mcx = my_bitmap->cx() / 2.0;
		double mcy = my_bitmap->cy() / 2.0;
		double ocx = obj_bitmap->cx() / 2.0;
		double ocy = obj_bitmap->cy() / 2.0;
		double max_distance_x = mcx + ocx;
		double max_distance_y = mcy + ocy;

		double mx = this->x() + mcx;
		double my = this->y() + mcy;
		double ox = obj->x() + ocx;
		double oy = obj->y() + ocy;
		double distance_x = mx - ox;
		double distance_y = my - oy;
		int add = 10;
		int offset = 1;
		double ddx = max_distance_x - std::abs(distance_x);
		double ddy = max_distance_y - std::abs(distance_y);
		if (ddx < add)
		{
			if (distance_x > 0)
			{
				ControlObjMgr::Instance().ChangeObjCoordinate(ddx + offset, 0);
			}
			else
			{
				ControlObjMgr::Instance().ChangeObjCoordinate(-ddx - offset, 0);
			}
		}
		if (ddy < add)
		{
			if (distance_y > 0)
			{
				ControlObjMgr::Instance().ChangeObjCoordinate(0, ddy + offset);
			}
			else
			{
				ControlObjMgr::Instance().ChangeObjCoordinate(0, -ddy - offset);
			}
		}
	}
	break;

	}
}
