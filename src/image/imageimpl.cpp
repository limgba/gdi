#include "bitmapimage.h"
#include "imageimpl.h"

ImageImpl::~ImageImpl()
{
	if (nullptr != m_mask_bitmap_image)
	{
		delete m_mask_bitmap_image;
		m_mask_bitmap_image = nullptr;
	}
}

void ImageImpl::SetMaskBitMapImage(BitMapImage* bitmap_image)
{
	m_mask_bitmap_image = bitmap_image;
}

BitMapImage* ImageImpl::GetMaskBitMapImage()
{
	return m_mask_bitmap_image;
}
