#include "imagemgr.h"
#include "image.h"
#include "../shape.h"
#include <algorithm>

BitMapImageMgr& BitMapImageMgr::Instance()
{
	static BitMapImageMgr mgr;
	return mgr;
}

BitMapImageMgr::BitMapImageMgr()
{
	m_dirty_rigid_body_count = 0;
	m_dirty_layer = false;
}

BitMapImageMgr::~BitMapImageMgr()
{
}

BitMapImage* BitMapImageMgr::GetBitMapImage(size_t index)
{
	if (index >= m_image_list.size())
	{
		return nullptr;
	}
	return m_image_list[index];
}

void BitMapImageMgr::CollisionCheck()
{
	if (0 == m_dirty_rigid_body_count)
	{
		return;
	}
	lmb::Rectangle rect1;
	lmb::Rectangle rect2;
	for (size_t i = 0; i < m_dirty_rigid_body_count && i < m_rigid_body_list.size(); ++i)
	{
		auto* image1 = m_rigid_body_list[i];
		if (nullptr == image1)
		{
			continue;
		}
		for (size_t j = i; j < m_rigid_body_list.size(); ++j)
		{
			auto* image2 = m_rigid_body_list[j];
			if (nullptr == image2)
			{
				continue;
			}
			if (image1 == image2)
			{
				continue;
			}
			rect1.left = image1->x();
			rect1.top = image1->y();
			rect1.right = image1->x() + image1->cx();
			rect1.bottom = image1->y() + image1->cy();

			rect2.left = image2->x();
			rect2.top = image2->y();
			rect2.right = image2->x() + image2->cx();
			rect2.bottom = image2->y() + image2->cy();

			if (!lmb::Impact(rect1, rect2))
			{
				continue;
			}
			BitMapImage::OnImpact(image1, image2);
		}
	}
	m_dirty_rigid_body_count = 0;
}

size_t BitMapImageMgr::ImageCount()
{
	return m_image_list.size();
}

void BitMapImageMgr::PushBitMapImage(BitMapImage* image)
{
	if (nullptr == image)
	{
		return;
	}
	image->ReLoadBitMapImage();
	m_image_list.push_back(image);

	if (image->IsRigidBody())
	{
		++m_dirty_rigid_body_count;
		m_rigid_body_list.push_back(image);
	}
}

void BitMapImageMgr::SelectAndBitBltAll()
{
	if (m_dirty_layer)
	{
		std::stable_sort(m_image_list.begin(), m_image_list.end(), [](BitMapImage* l, BitMapImage* r)->bool
			{
				return l->GetLayer() < r->GetLayer();
			});
		m_dirty_layer = false;
	}
	for (const auto& image : m_image_list)
	{
		image->SelectAndBitBlt();
	}
}

void BitMapImageMgr::DeleteAllBitMapImage()
{
	for (auto& image : m_image_list)
	{
		if (nullptr == image)
		{
			continue;
		}
		delete image;
		image = nullptr;
	}
	m_image_list.clear();
	m_dirty_rigid_body_count = 0;
	m_rigid_body_list.clear();
}

void BitMapImageMgr::DirtyLayer()
{
	m_dirty_layer = true;
}

void BitMapImageMgr::OnBitMapImageMove(BitMapImage* image)
{
	if (nullptr == image)
	{
		return;
	}
	size_t i = m_dirty_rigid_body_count;
	bool is_find = false;
	for (; i < m_rigid_body_list.size(); ++i)
	{
		if (image == m_rigid_body_list[i])
		{
			is_find = true;
			break;
		}
	}
	if (!is_find)
	{
		return;
	}
	if (m_dirty_rigid_body_count < m_rigid_body_list.size() && i < m_rigid_body_list.size())
	{
		std::swap(m_rigid_body_list[m_dirty_rigid_body_count], m_rigid_body_list[i]);
		++m_dirty_rigid_body_count;
	}
}
