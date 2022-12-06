#include "animation.h"

void Animation::Push(FrameImage frame_image)
{
	m_image_list.push_back(frame_image);
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
	FrameImage* frame_image = &m_image_list[m_index];
	if (nullptr == frame_image)
	{
		return;
	}

	clock_t diff_clock = now_clock - m_clock;
	if (diff_clock >= frame_image->intervel_ms)
	{
		++m_index;
		if (m_index >= m_image_list.size())
		{
			return;
		}
		frame_image = &m_image_list[m_index];
		if (nullptr == frame_image)
		{
			return;
		}
	}
	if (nullptr == frame_image->image)
	{
		return;
	}
	frame_image->image->SelectAndBitBlt();
}

double Animation::GetLayer(size_t index) const
{
	if (index >= m_image_list.size())
	{
		return 0.0;
	}
	auto* image = m_image_list[index].image;
	if (nullptr == image)
	{
		return 0.0;
	}
	return image->GetLayer();
}
