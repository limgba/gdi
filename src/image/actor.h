#pragma once
#include "image.h"

class Actor : public BitMapImage
{
public:
	Actor(LPCWSTR path, int x, int y);
	virtual ~Actor();

	virtual void LoadBitMapImage();
	virtual void SelectAndBitBlt() const;
	
private:
	HBITMAP m_hbitmap_mask = nullptr;
};
