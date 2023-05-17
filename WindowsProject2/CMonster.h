#pragma once
#include "CObject.h"

class CTexture;

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
    virtual CMonster* Clone() { return new CMonster(*this); }
	virtual void render(HDC _dc);   //요기 추가- 성균


private:
    Vec2    m_vCenterPos;
    float   m_fSpeed;
    float   m_fMaxDistance;
    int     m_iDir;
    
    int     m_iHP;
	CTexture* m_mTex;   // 요기 추가 - 성균

};