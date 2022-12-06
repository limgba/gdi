#pragma once
#include "animation.h"


class AnimationMgr
{
public:
	static AnimationMgr& Instance();

	void Play();
	void PushAnimation(const Animation& animation);
	void SortAnimation();
	
private:
	bool m_need_sort = false;
	int m_play_count = 0;
	std::vector<Animation> m_animation_list;
};
