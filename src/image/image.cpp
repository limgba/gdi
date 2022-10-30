#include "image.h"
#include "../hdcmgr/hdcmgr.h"
#include "imagemgr.h"

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif


BitMapImage::BitMapImage(LPCWSTR path, int x, int y)
{
	m_path = path;
	m_x = x;
	m_y = y;
}

BitMapImage::~BitMapImage()
{
	if (nullptr != m_hbitmap)
	{
		DeleteObject(m_hbitmap);
	}
}

void BitMapImage::ReLoadBitMapImage()
{
	this->LoadBitMapImage();
	this->SetCoordinate(m_x, m_y);
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
void BitMapImage::SetCoordinate(int x, int y)
{
	m_x = x;
	m_y = y;
	if (this->IsRigidBody())
	{
		BitMapImageMgr::Instance().OnBitMapImageMove(this);
	}
}
void BitMapImage::SelectAndBitBlt() const
{
	HDC hdc1 = HdcMgr::Instance().GetHdc1();
	HDC hdc2 = HdcMgr::Instance().GetHdc2();

	SelectObject(hdc2, m_hbitmap);
	BitBlt(hdc1, m_x, m_y, m_cx, m_cy, hdc2, 0, 0, SRCCOPY);
}

void BitMapImage::SetLayer(double layer)
{
	m_layer = layer;
	BitMapImageMgr::Instance().DirtyLayer();
}

void BitMapImage::SetObjType(int obj_type)
{
	m_obj_type = obj_type;
}

int BitMapImage::GetObjType() const
{
	return m_obj_type;
}

void BitMapImage::OnImpact(BitMapImage* image1, BitMapImage* image2)
{
	if (nullptr == image1 || nullptr == image2)
	{
		return;
	}
	int obj_type1 = std::min(image1->GetObjType(), image2->GetObjType());
	int obj_type2 = std::max(image1->GetObjType(), image2->GetObjType());
	const int obj_type = LeftOffsetShort(obj_type1, obj_type2);
	if (image1->GetObjType() != obj_type1)
	{
		std::swap(image1, image2);
	}
	switch (obj_type)
	{
	case BITMAP_IMAGE_OBJ_TYPE_PLAYER_SKILL:
	{
		BitMapImage::OnImpactPlayerSkill(image1, image2);
	}
	break;
	case BITMAP_IMAGE_OBJ_TYPE_PLAYER_MONSTER:
	{
		BitMapImage::OnImpactPlayerMonster(image1, image2);
	}
	break;
	case BITMAP_IMAGE_OBJ_TYPE_PLAYER_DROP:
	{
		BitMapImage::OnImpactPlayerDrop(image1, image2);
	}
	break;
	case BITMAP_IMAGE_OBJ_TYPE_MONSTER_SKILL:
	{
		BitMapImage::OnImpactMonsterSkill(image1, image2);
	}
	break;
	}
}

void BitMapImage::OnImpactPlayerSkill(BitMapImage* image1, BitMapImage* image2)
{
	if (nullptr == image1 || nullptr == image2)
	{
		return;
	}
	image1->SetCoordinate(0, 0);
}

void BitMapImage::SetIsRigidbody(bool is_rigid_body)
{
	m_is_rigid_body = is_rigid_body;
}

void BitMapImage::OnImpactPlayerMonster(BitMapImage* image1, BitMapImage* image2)
{
}

void BitMapImage::OnImpactPlayerDrop(BitMapImage* image1, BitMapImage* image2)
{
}

void BitMapImage::OnImpactMonsterSkill(BitMapImage* image1, BitMapImage* image2)
{
}

bool BitMapImage::IsRigidBody() const
{
	return m_is_rigid_body;
}

