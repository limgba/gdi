#include "animationmgr.h"
#include <algorithm>

AnimationMgr& AnimationMgr::Instance()
{
	static AnimationMgr mgr;
	return mgr;
}

void AnimationMgr::Play()
{
	clock_t now_clock = clock();
	for (auto& animation : m_animation_list)
	{
		animation.Play(now_clock);
	}
	++m_play_count;
	if (m_play_count >= FRAME_PER_SECOND)
	{
		m_play_count = 0;
	}
	clock_t play_clock = clock();
	clock_t diff_clock = play_clock - now_clock;
	if (diff_clock < FRAME_MILLISECOND)
	{
		Sleep(FRAME_MILLISECOND - diff_clock);
		if (0 == m_play_count)
		{
			Sleep(FILL_THE_FRAME);
		}
	}
}

void AnimationMgr::PushAnimation(const Animation& animation)
{
	m_animation_list.push_back(animation);
}

void AnimationMgr::SortAnimation()
{
	std::sort(m_animation_list.begin(), m_animation_list.end(), [](const Animation& l, const Animation& r)
		{
			return l.GetLayer(0) < r.GetLayer(0);
		});
}

