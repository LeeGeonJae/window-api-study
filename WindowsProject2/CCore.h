#pragma once
#include "pch.h"

class CCore
{
public:
	SINGLE(CCore);

private:
	HWND	m_hWnd;					// ���� ������ �ڵ�
	POINT	m_ptResolution;			// ���� ������ �ػ�
	HDC		m_hDC;


public:
	int Init(HWND _hWnd, POINT _ptResoultion);
	void progress();

private:
	void update();
	void render();

};