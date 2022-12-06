#pragma once
#include <vector>
#include <time.h>
#include "image.h"

// ÿ��֡��
static const int FRAME_PER_SECOND = 60;
// ÿ����Ҫ��֡
static const int FILL_THE_FRAME = 4;
// ÿ֡���ĺ�����
static const int FRAME_MILLISECOND = static_cast<int>(1.0 / FRAME_PER_SECOND * 1000);

struct FrameImage
{
	int intervel_ms = 0;
	int next_index = 0;
	BitMapImage* image = nullptr;
};

class Animation
{
public:
	void Push(FrameImage frame_image);
	void InitClock();
	void Play(clock_t now_clock);
	double GetLayer(size_t index) const;
	
private:
	size_t m_index = 0;
	clock_t m_clock = 0;
	std::vector<FrameImage> m_image_list;
};
