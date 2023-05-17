#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float m_fTheta;
    OBJECT_DIR  m_dir;
    float m_fLifeTiem;

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(OBJECT_DIR _vDir)
    { 
        m_dir = _vDir;
    }


public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

    // 객체들이 복사 생성자를 호출할 때, 클론 리턴
    virtual CMissile* Clone() { return new CMissile(*this); }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMissile();
    ~CMissile();
};