#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"


CTimeMgr::CTimeMgr()
	:m_llcurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_iCallCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ�� (õ��)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llcurCount);

	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llcurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// ����ī��Ʈ ���� ���簪���� ���� (�������� ����� ���ؼ�)
	m_llPrevCount = m_llcurCount;

	// ���࿡ �ߴ����� ��� �˻��ϴ� ����� ���¶�� �ð��� �帣�� ���� �����ϱ� ���� ������ ��ó����
#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT;	// DT ����

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;
		
		// ������ ���¸� ������ â ���� ����
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d,    DT : %lf", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHWnd(), szBuffer);
	}
}
