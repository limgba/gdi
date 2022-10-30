#pragma once
#include <vector>

class BitMapImage;

class BitMapImageMgr
{
public:
	static BitMapImageMgr& Instance();
	BitMapImageMgr();
	~BitMapImageMgr();

	BitMapImage* GetBitMapImage(size_t index);
	void CollisionCheck();

	size_t ImageCount();
	void PushBitMapImage(BitMapImage* image);
	void SelectAndBitBltAll();
	void DeleteAllBitMapImage();

	void DirtyLayer();
	void OnBitMapImageMove(BitMapImage* image);

private:
	std::vector<BitMapImage*> m_image_list;

	bool m_dirty_layer;
	size_t m_dirty_rigid_body_count;
	std::vector<BitMapImage*> m_rigid_body_list;
};