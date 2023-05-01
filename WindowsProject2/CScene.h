#pragma once

// ���漱��
class CObject;

class CScene
{
private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName;							// Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	// ���� ���Ե� ���� �Լ��� �ڽ� Ŭ�������� �����ؾߵ� �Լ��� ���� �˸��� �뵵�̴�
	virtual void Enter() = 0;		// �ش� Scene�� ���� �� ȣ��
	virtual void Exit() = 0;		// �ش� Scene�� Ż�� �� ȣ��

protected:
	// �����θ� ����� ����� �ش� �Լ��� �ζ��� ó���Ǿ� �Լ� ȣ�� ������ ������ �ʾ� ���ɿ� ���̰� ���� ����.
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); };

public:
	CScene();
	virtual ~CScene();

};

