#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llcurCount;
	LARGE_INTEGER	m_llFrequency;

	// FPS
	// 1프레임당 시간 (Delta Time)

public:
	void init();
	void update();
};

