#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
public:
    CMonster();
    ~CMonster();

public:
    float GetSpeed() { return m_fSpeed; }

    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();

private:
    Vec2    m_vCenterPos;
    float   m_fSpeed;
    float   m_fMaxDistance;
    int     m_iDir;
};

