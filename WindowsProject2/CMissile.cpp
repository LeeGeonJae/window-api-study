#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fTheta((float)PI / 2.f)
	, m_dir{}
	, m_fLifeTiem(2.0f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	m_fLifeTiem -= fDT;
	if (m_fLifeTiem <= 0)
	{
		DeleteObject(this);
	}

	Vec2 vPos = GetPos();

	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y += 600.f * sinf(m_fTheta) * fDT;

	switch (m_dir)
	{
	case OBJECT_DIR::UP:
		vPos.y -= 1.5f * BOARD_TILE * fDT;
		break;
	case OBJECT_DIR::LEFT:
		vPos.x -= 1.5f * BOARD_TILE * fDT;
		break;
	case OBJECT_DIR::RIGHT:
		vPos.x += 1.5f * BOARD_TILE * fDT;
		break;
	case OBJECT_DIR::DOWN:
		vPos.y += 1.5f * BOARD_TILE * fDT;
		break;
	default:
		break;
	}

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2)
		, (int)(vPos.x + vScale.x / 2), (int)(vPos.y + vScale.y / 2));

	Component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
