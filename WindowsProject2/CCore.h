#pragma once
#include "pch.h"

class CCore
{
public:
	SINGLE(CCore);
public:
	int Init(HWND _hWnd, POINT _ptResoultion);
	void progress();

private:
	void CreateBrushPen();

public:
	HWND GetMainHWnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

private:
	HWND	m_hWnd;					// 메인 윈도우 핸들
	POINT	m_ptResolution;			// 메인 윈도우 해상도
	HDC		m_hDC;

	HBITMAP	m_hBit;
	HDC		m_memDC;

	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];
};