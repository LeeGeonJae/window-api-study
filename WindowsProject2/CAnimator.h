#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;			// 모든 Animation
	CAnimation*					m_pCurAnim;			// 현재 재생중인 Animation
	CObject*					m_pOwner;			// Animator 소유 오브젝트
	bool						m_bRepeat;			// 반복재생 여부

public:
	CObject* GetObj() { return m_pOwner; }

	CAnimation* GetCurAnim() const
	{
		return m_pCurAnim;
	}
public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSilceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void render(HDC _dc);
	void finalupdate();


public:
	CAnimator();
	~CAnimator();

	// 컴포넌트이기 때문에 해당 오브젝트에서 private 변수에 접근할 수 있도록 friend class Object로 설정
	friend class CObject;
};