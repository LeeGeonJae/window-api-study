#pragma once
class CCollider;

class CObject
{
public:
	virtual void update() = 0;
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void Component_render(HDC _dc);
	

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }

	bool IsDead() { return !m_bAlibe; }

public:
	void CreateCollider();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { m_bAlibe = false; }

public:
	CObject();
	virtual ~CObject();

private:
	Vec2	m_vPos;
	Vec2	m_vScale;

	CCollider* m_pCollider;

	wstring m_strName;

	bool m_bAlibe;

	friend class CEventMgr;
};
