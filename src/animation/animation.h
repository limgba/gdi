#pragma once
#include <vector>
#include <time.h>

class ImageBase;
class Obj;

// 每秒帧数
static const int FRAME_PER_SECOND = 60;
// 每秒需要补帧
static const int FILL_THE_FRAME = 4;
// 每帧消耗毫秒数
static const int FRAME_MILLISECOND = static_cast<int>(1.0 / FRAME_PER_SECOND * 1000);


class Animation
{
public:
	~Animation();
	void SetObj(Obj* obj);
	Obj* GetObj();
	void PushImageBase(ImageBase* image_base);
	void InitClock();
	void Play(clock_t now_clock);
	void SetLayer(double layer);
	double GetLayer() const;
	const std::vector<ImageBase*>& GetImageVec();
	ImageBase* GetImageBase();
	
private:
	size_t m_index = 0;
	clock_t m_clock = 0;
	double m_layer = 0.0;
	std::vector<ImageBase*> m_image_list;
	Obj* m_obj = nullptr;
};
