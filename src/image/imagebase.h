#pragma once
class BitMapImage;

class ImageBase
{
public:
	virtual ~ImageBase();
	void SetIntervalMs(long interval_ms);
	long GetIntervalMs();
	void SetNextIndex(int next_index);
	int GetNextIndex();
	void SetBitMapImage(BitMapImage* bitmap_image);
	BitMapImage* GetBitMapImage();
	virtual void SetMaskBitMapImage(BitMapImage* bitmap_image);
	virtual BitMapImage* GetMaskBitMapImage();

private:
	long m_interval_ms = 0;
	int m_next_index = 0;
	BitMapImage* m_bitmap_image = nullptr;
};
