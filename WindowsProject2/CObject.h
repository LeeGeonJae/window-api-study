#pragma once
class CCollider;
class CAnimator;

class CObject
{
public:
	virtual void update() = 0;
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void Component_render(HDC _dc);

	// ������Ʈ ������ �� �ʿ��� �Լ� ( ���� ���� �Լ�, �ڽ� Ŭ�������� ���� �ʿ� )
	virtual CObject* Clone() = 0;

public:
	// ��ġ, ũ�� ����
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	// �̸� ����
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	// ������Ʈ ��������
	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }

	// ���� ������Ʈ���� Ȯ���ϱ� ���� �Լ�
	bool IsDead() { return !m_bAlibe; }

public:
	// ������Ʈ ����
	void CreateCollider();
	void CreateAnimator();

	// �ݸ��� �̺�Ʈ �߻�
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	// ���� �����ӿ� ���� ������Ʈ ����
	void SetDead() { m_bAlibe = false; }

public:
	CObject();									// �⺻ ������
	CObject(const CObject& _origin);			// ���� ������
	virtual ~CObject();							// �Ҹ���

private:
	Vec2		m_vPos;			// ��ġ
	Vec2		m_vScale;		// ũ��
	wstring		m_strName;		// ��ü �̸�
	bool		m_bAlibe;		// ��ü ����

	// Component
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;


	friend class CEventMgr;
};
