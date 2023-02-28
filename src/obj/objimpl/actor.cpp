#include "actor.h"
#include "../../animation/animation.h"
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
		ControlObjMgr::Instance().ChangeObjCoordinate(0, 0);
	}
	break;
	}
}
