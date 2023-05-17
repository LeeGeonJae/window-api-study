#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"

#include "CTexture.h"	//요기 추가	- 성균
#include "CResMgr.h"	//요기 추가	- 성균


CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHP(5)
	, m_mTex(nullptr)	//요기 추가	-성균
{
	// Texture 로딩하기
	m_mTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\monster1.bmp");	//요기 추가 - 성균


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	// 진행 방향으로 시간당 m_fSpeed 만큼 이동
	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// 배회 거리 기준량을 넘어섰는지 확인
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if (0.f < fDist)
	{
		// 방향 변경
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}

void CMonster::render(HDC _dc)			//요기 추가- 성균
{
	int iWidth = (int)m_mTex->Width();
	int iHeight = (int)m_mTex->Height();

	Vec2 vPos = GetPos();

	// BitBlt과 비슷하지만 특정 픽셀 색상을 무시한 기능을 추가한 BitBlt이다
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(iWidth / 8))
		, (int)(vPos.y - (float)(iHeight / 8))
		, iWidth / 4, iHeight / 4
		, m_mTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	// 컴포넌트 (충돌체, etc...) 가 있는 경우 렌더
	Component_render(_dc);

}



void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP--;

		if (m_iHP <= 0)
			DeleteObject(this);
	}
}