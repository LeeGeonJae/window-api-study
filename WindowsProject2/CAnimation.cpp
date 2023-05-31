#include "pch.h"
#include "CAnimation.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CTimeMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();	

	vPos += m_vecFrm[m_iCurFrm].vOffset;		// Object Position에 Offset만큼 추가 이동위치

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSilce.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSilce.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSilce.x			   )
		, (int)(m_vecFrm[m_iCurFrm].vSilce.y			   )
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x				   )
		, (int)(m_vecFrm[m_iCurFrm].vLT.y				   )
		, (int)(m_vecFrm[m_iCurFrm].vSilce.x			   )
		, (int)(m_vecFrm[m_iCurFrm].vSilce.y			   )
		, RGB(0, 64, 128));
}

void CAnimation::finalupdate()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		m_iCurFrm++;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = 0;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSilceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; i++)
	{
		frm.fDuration = _fDuration;
		frm.vSilce = _vSilceSize;
		frm.vLT = _vLT + _vStep * i;

		// 정보 다 입력하고 vector 배열에 입력
		m_vecFrm.push_back(frm);
	}
}
