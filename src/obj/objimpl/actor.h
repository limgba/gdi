#pragma once
#include "../obj.h"

class Actor : public Obj
{
public:
	virtual int GetObjType() { return BITMAP_IMAGE_OBJ_TYPE_PLAYER; }
	void OnImpact(Obj* obj);
	
};