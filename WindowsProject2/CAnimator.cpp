#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	:m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_map(m_mapAnim);
}

// 현재 재생중인 애니메이션 update()
void CAnimator::update()
{

}

// 현재 재생중인 애니메이션 render
void CAnimator::render(HDC _dc)
{
	if (nullptr != GetCurAnim())
	{
		GetCurAnim()->render(_dc);
	}
}


void CAnimator::finalupdate()
{
	if (nullptr != GetCurAnim())
	{
		GetCurAnim()->finalupdate();

		// 애니메이션의 반복 여부를 체크한 bRepeat가 true이고 Animation 객체에서 애니메이션의 마지막을 체크하는 finish의 상태를 가져와서
		// Animation의 프레임을 0으로 세팅하고 finish 변수를 false로 세팅
		if (m_bRepeat && GetCurAnim()->IsFinish())
		{
			GetCurAnim()->SetFrame(0);
		}
	}
}

// 애니메이션 생성
void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSilceSize, Vec2 _vStep
								, float _fDuration, UINT _iFrameCount)
{
	// 같은 이름을 사용하는 애니메이션이 있는지 체크
	// 같은 이름을 사용하는 애니메이션이 있을 경우 assert에서 오류 체크
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	// 애니메이션 객체를 생성 후 이름, 컴포넌트 소유 객체, 
	// m_mapAnim에 이름에 따라 관리해주기 위한 애니메이션 map으로 등록
	pAnim = new CAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(_strName, pAnim));

	// 애니메이션 정보를 가지고 생성
	pAnim->Create(_pTex, _vLT, _vSilceSize, _vStep, _fDuration, _iFrameCount);
}

// 똑같은 이름의 애니메이션 찾는 함수
CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

// 인자로 받은 이름의 애니메이션 재생
void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
	m_pCurAnim->m_bFinish = false;
}

