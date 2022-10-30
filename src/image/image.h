#pragma once
#include "../../../framework.h"
#include <string>

enum BITMAP_IMAGE_OBJ_TYPE
{
	BITMAP_IMAGE_OBJ_TYPE_NONE = 0,
	BITMAP_IMAGE_OBJ_TYPE_BACK_GROUND,
	BITMAP_IMAGE_OBJ_TYPE_PLAYER,
	BITMAP_IMAGE_OBJ_TYPE_MONSTER,
	BITMAP_IMAGE_OBJ_TYPE_SKILL = 100,
	BITMAP_IMAGE_OBJ_TYPE_DROP,
};

constexpr int LeftOffsetShort(int a, int b)
{
	constexpr int offset = static_cast<int>(sizeof(short) * CHAR_BIT);
	return (a << offset) + b;
}

static const int BITMAP_IMAGE_OBJ_TYPE_PLAYER_SKILL = LeftOffsetShort(BITMAP_IMAGE_OBJ_TYPE_PLAYER, BITMAP_IMAGE_OBJ_TYPE_SKILL);
static const int BITMAP_IMAGE_OBJ_TYPE_PLAYER_MONSTER = LeftOffsetShort(BITMAP_IMAGE_OBJ_TYPE_PLAYER,  BITMAP_IMAGE_OBJ_TYPE_MONSTER);
static const int BITMAP_IMAGE_OBJ_TYPE_PLAYER_DROP = LeftOffsetShort(BITMAP_IMAGE_OBJ_TYPE_PLAYER, BITMAP_IMAGE_OBJ_TYPE_DROP);
static const int BITMAP_IMAGE_OBJ_TYPE_MONSTER_SKILL = LeftOffsetShort(BITMAP_IMAGE_OBJ_TYPE_MONSTER, BITMAP_IMAGE_OBJ_TYPE_SKILL);

//const std::wstring IMAGE_PATH_HEAD(L"../../WindowsProject1/gdi/resource/image/");
const std::wstring IMAGE_PATH_HEAD(L"gdi/resource/image/");

class BitMapImage
{
public:
	BitMapImage(LPCWSTR path, int x, int y);
	virtual ~BitMapImage();
	void ReLoadBitMapImage();
	virtual void LoadBitMapImage();
	void SetCoordinate(int x, int y);
	virtual void SelectAndBitBlt() const;

	int x() { return m_x; }
	int y() { return m_y; }
	int cx() { return m_cx; }
	int cy() { return m_cy; }

	void SetLayer(double layer);
	double GetLayer() { return m_layer; }

	void SetObjType(int obj_type);
	int GetObjType() const;
	static void OnImpact(BitMapImage* image1, BitMapImage* image2);
	static void OnImpactPlayerSkill(BitMapImage* image1, BitMapImage* image2);
	static void OnImpactPlayerMonster(BitMapImage* image1, BitMapImage* image2);
	static void OnImpactPlayerDrop(BitMapImage* image1, BitMapImage* image2);
	static void OnImpactMonsterSkill(BitMapImage* image1, BitMapImage* image2);

public:
	void SetIsRigidbody(bool is_rigid_body);
	bool IsRigidBody() const;
	
protected:
	LPCWSTR m_path;
	HBITMAP m_hbitmap = nullptr;
	int m_x = 0;
	int m_y = 0;
	int m_cx = 0;
	int m_cy = 0;
	int m_auto_inc_id = 0;
	double m_layer = 0.0;
	int m_obj_type = BITMAP_IMAGE_OBJ_TYPE_NONE;
	bool m_is_rigid_body = false;
};
