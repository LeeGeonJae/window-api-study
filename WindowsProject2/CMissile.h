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

    // ��ü���� ���� �����ڸ� ȣ���� ��, Ŭ�� ����
    virtual CMissile* Clone() { return new CMissile(*this); }

public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMissile();
    ~CMissile();
};