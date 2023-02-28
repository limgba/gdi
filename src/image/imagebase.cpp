#include "imagebase.h"
#include "bitmapimage.h"

ImageBase::~ImageBase()
{
	if (nullptr != m_bitmap_image)
	{
		delete m_bitmap_image;
		m_bitmap_image = nullptr;
	}
}

void ImageBase::SetIntervalMs(long interval_ms)
{
	m_interval_ms = interval_ms;
}

long ImageBase::GetIntervalMs()
{
	return m_interval_ms;
}

void ImageBase::SetNextIndex(int next_index)
{
	m_next_index = next_index;
}

int ImageBase::GetNextIndex()
{
	return m_next_index;
}

void ImageBase::SetBitMapImage(BitMapImage* bitmap_image)
{
	m_bitmap_image = bitmap_image;
	if (nullptr != m_bitmap_image)
	{
		m_bitmap_image->LoadBitMapImage();
	}
}

BitMapImage* ImageBase::GetBitMapImage()
{
	return m_bitmap_image;
}

void ImageBase::SetMaskBitMapImage(BitMapImage* bitmap_image)
{
}

BitMapImage* ImageBase::GetMaskBitMapImage()
{
	return nullptr;
}

