#include "animation.h"
#include "../image/imagebase.h"
#include "../image/bitmapimage.h"
#include "../obj/rigidbodymgr.h"
#include "../obj/obj.h"

Animation::~Animation()
{
	for (ImageBase* image_base : m_image_list)
	{
		delete image_base;
		image_base = nullptr;
	}
	m_image_list.clear();
}

void Animation::SetObj(Obj* obj)
{
	if (nullptr == obj)
	{
		return;
	}
	m_obj = obj;
}

Obj* Animation::GetObj()
{
	return m_obj;
}

void Animation::PushImageBase(ImageBase* image_base)
{
	if (nullptr == image_base)
	{
		return;
	}
	m_image_list.push_back(image_base);
}

void Animation::InitClock()
{
	m_clock = clock();
}

void Animation::Play(clock_t now_clock)
{
	if (m_index >= m_image_list.size())
	{
		return;
	}
	ImageBase* image_base = m_image_list[m_index];
	if (nullptr == image_base)
	{
		return;
	}

	if (image_base->GetIntervalMs() > 0 && now_clock - m_clock >= image_base->GetIntervalMs())
	{
		m_index = image_base->GetNextIndex();
		if (m_index >= m_image_list.size())
		{
			return;
		}
		image_base = m_image_list[m_index];
		if (nullptr == image_base)
		{
			return;
		}
	}
	if (nullptr == image_base->GetBitMapImage())
	{
		return;
	}
	switch (m_obj->GetObjType())
	{
	case BITMAP_IMAGE_OBJ_TYPE_SCENE:
	{
		image_base->GetBitMapImage()->SelectAndBitBlt(m_obj->x(), m_obj->y(), SRCCOPY);
	}
	break;
	default:
	{
		image_base->GetMaskBitMapImage()->SelectAndBitBlt(m_obj->x(), m_obj->y(), SRCAND);
		image_base->GetBitMapImage()->SelectAndBitBlt(m_obj->x(), m_obj->y(), SRCPAINT);
	}
	break;
	}
}

void Animation::SetLayer(double layer)
{
	m_layer = layer;
}

double Animation::GetLayer() const
{
	return m_layer;
}

const std::vector<ImageBase*>& Animation::GetImageVec()
{
	return m_image_list;
}

ImageBase* Animation::GetImageBase()
{
	if (m_index >= m_image_list.size())
	{
		return nullptr;
	}
	return m_image_list[m_index];
}

