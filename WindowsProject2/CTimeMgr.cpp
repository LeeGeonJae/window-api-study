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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llcurCount);

	// �ʴ� ī��Ʈ Ƚ�� (õ��)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{

}