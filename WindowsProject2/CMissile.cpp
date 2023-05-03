#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta(45.f)
{
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	float MissileSpeed = sqrt(pow(600, 2) / 2);

	vPos.x += MissileSpeed * cosf(m_fTheta) * fDT;
	vPos.y += MissileSpeed * sinf(m_fTheta) * fDT;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2)
		, (int)(vPos.x + vScale.x / 2), (int)(vPos.y + vScale.y / 2));
}