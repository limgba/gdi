#pragma once
#include "../../../framework.h"
#include <string>

//const std::wstring IMAGE_PATH_HEAD(L"../../WindowsProject1/gdi/resource/image/");
const std::wstring IMAGE_PATH_HEAD(L"gdi/resource/image/");

class BitMapImage
{
public:
	BitMapImage(LPCWSTR path);
	virtual ~BitMapImage();
	void LoadBitMapImage();
	void SelectAndBitBlt(int x, int y, int operations) const;

	int cx() { return m_cx; }
	int cy() { return m_cy; }

protected:
	LPCWSTR m_path;
	HBITMAP m_hbitmap = nullptr;
	int m_cx = 0;
	int m_cy = 0;
};
