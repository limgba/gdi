#pragma once
#include "imagebase.h"

class ImageImpl : public ImageBase
{
public:
	virtual ~ImageImpl();
	virtual void SetMaskBitMapImage(BitMapImage* bitmap_image);
	virtual BitMapImage* GetMaskBitMapImage();

private:
	BitMapImage* m_mask_bitmap_image = nullptr;
};
