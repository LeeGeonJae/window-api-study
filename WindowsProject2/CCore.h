#pragma once
#include "pch.h"

class CCore
{
public:
	SINGLE(CCore);

private:
	HWND	m_hWnd;					// 메인 윈도우 핸들
	POINT	m_ptResolution;			// 메인 윈도우 해상도
	HDC		m_hDC;

	HBITMAP	m_hBit;
	HDC		m_memDC;

public:
	int Init(HWND _hWnd, POINT _ptResoultion);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHWnd() { return m_hWnd; }
};