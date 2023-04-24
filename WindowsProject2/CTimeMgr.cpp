#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr()
	:m_llcurCount{}
	, m_llFrequency{}
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llcurCount);

	// 초당 카운트 횟수 (천만)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{

}