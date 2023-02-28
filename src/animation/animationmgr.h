#pragma once
#include <vector>
class Animation;


class AnimationMgr
{
public:
	static AnimationMgr& Instance();
	void DeleteAllAnimation();

	void Play();
	void PushAnimation(Animation* animation);
	void DeleteAnimation(Animation* delete_animation);
	size_t AnimationSize();
	void SortAnimation();
	void DirtyLayer();			
	
private:
	bool m_dirty_layer = false;
	int m_play_count = 0;
	std::vector<Animation*> m_animation_list;
};
