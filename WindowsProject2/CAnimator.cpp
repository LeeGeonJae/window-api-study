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

// ���� ������� �ִϸ��̼� update()
void CAnimator::update()
{

}

// ���� ������� �ִϸ��̼� render
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

		// �ִϸ��̼��� �ݺ� ���θ� üũ�� bRepeat�� true�̰� Animation ��ü���� �ִϸ��̼��� �������� üũ�ϴ� finish�� ���¸� �����ͼ�
		// Animation�� �������� 0���� �����ϰ� finish ������ false�� ����
		if (m_bRepeat && GetCurAnim()->IsFinish())
		{
			GetCurAnim()->SetFrame(0);
		}
	}
}

// �ִϸ��̼� ����
void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSilceSize, Vec2 _vStep
								, float _fDuration, UINT _iFrameCount)
{
	// ���� �̸��� ����ϴ� �ִϸ��̼��� �ִ��� üũ
	// ���� �̸��� ����ϴ� �ִϸ��̼��� ���� ��� assert���� ���� üũ
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	// �ִϸ��̼� ��ü�� ���� �� �̸�, ������Ʈ ���� ��ü, 
	// m_mapAnim�� �̸��� ���� �������ֱ� ���� �ִϸ��̼� map���� ���
	pAnim = new CAnimation;
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(_strName, pAnim));

	// �ִϸ��̼� ������ ������ ����
	pAnim->Create(_pTex, _vLT, _vSilceSize, _vStep, _fDuration, _iFrameCount);
}

// �Ȱ��� �̸��� �ִϸ��̼� ã�� �Լ�
CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

// ���ڷ� ���� �̸��� �ִϸ��̼� ���
void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
	m_pCurAnim->m_bFinish = false;
}

