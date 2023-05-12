#pragma once

// 전방선언
class CObject;

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	void finalupdate();
	void render(HDC _dc);

	// 값이 기입된 가상 함수는 자식 클래스에서 구현해야될 함수인 것을 알리는 용도이다
	virtual void Enter() = 0;		// 해당 Scene에 진입 시 호출
	virtual void Exit() = 0;		// 해당 Scene을 탈출 시 호출

public:
	// 구현부를 헤더에 만들면 해당 함수는 인라인 처리되어 함수 호출 스택이 생기지 않아 성능에 차이가 많이 없다.
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_arrObj[(UINT)_eType].push_back(_pObj); };

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)	{	return m_arrObj[(UINT)_eType];	}

private:
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// 오브젝트를 저장 및 관리할 벡터를 그룹 갯수만큼 선언
	wstring				m_strName;							// Scene 이름
};