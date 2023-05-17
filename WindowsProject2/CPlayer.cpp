#include "pch.h"
#include "CPlayer.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayerIdleState.h"
// 기본 생성자
// 컴포넌트 추가할 곳
CPlayer::CPlayer()
	:m_fMoveDelay(0.5f),
	m_fShootDelay(0),
	m_fMoveMent(120.0f),
	m_fMoveTerm(0.2f),
	m_eCurDir(OBJECT_DIR::UP),
	m_ePastDir(OBJECT_DIR::UP),
	m_bCanMove(true),
	m_ptBoardPos{},
	m_eCurMoveState(PLAYER_MOVE_STATE::IDLE),
	m_ePastMoveState(PLAYER_MOVE_STATE::IDLE),
	m_eCurAttackState(PLAER_ATTACK_STATE::IDLE),
	m_fTimeLag(m_fTimeLagTerm)
{
	// Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	// Collider 세팅하기
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(30.f, 50.f));

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link1.bmp");

	// Animation 세팅하기
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE_UP", pTex, Vec2(17.f, 26.f), Vec2(28.f, 58.f), Vec2(28.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"IDLE_DOWN", pTex, Vec2(37.f, 56.f), Vec2(28.f, 58.f), Vec2(28.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(67.f, 86.f), Vec2(28.f, 58.f), Vec2(28.f, 0.f), 0.3f, 4);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(97.f, 116.f), Vec2(28.f, 58.f), Vec2(28.f, 0.f), 0.3f, 4);
	
	GetAnimator()->CreateAnimation(L"Shoot", pTex, Vec2(50.f, 50.f), Vec2(28.f, 58.f), Vec2(28.f, 0.f), 0.3f, 4);
	GetAnimator()->Play(L"IDLE_UP", true);

	// Animation Offset 위치 세팅하기 예제
	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE");
	//for (int i = 0; i < pAnim->GetMaxFrame(); i++)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -0.f); 
	//m_pState = new CPlayerIdleState;
}

CPlayer::~CPlayer()
{
	//delete m_pState;
}

void CPlayer::update()
{
	UpateState();
	UpdateMove();
	UpdateAnimation();
	m_ePastMoveState = m_eCurMoveState;
	m_ePastDir = m_eCurDir;
}

void CPlayer::render(HDC _dc)
{
	// 컴포넌트 (충돌체, etc...) 가 있는 경우 렌더
	// 컴포넌트 (Collider, Animator)
	Component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(GetDir());

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::UpateState()
{
	
	// IDLE 상태의 변화
	if (m_eCurMoveState == PLAYER_MOVE_STATE::IDLE)
	{

		if (KEY_HOLD(KEY::UP) && m_ptBoardPos.y != 0)
		{
			m_fTimeLag -= fDT;
			m_eCurDir = OBJECT_DIR::UP;

			if (m_fTimeLag <= 0 && m_eCurDir == m_ePastDir)
			{
				m_eCurMoveState = PLAYER_MOVE_STATE::MOVE;
			}
		}
		if (KEY_HOLD(KEY::DOWN) && m_ptBoardPos.y != BOARD_TILE - 1)
		{
			m_fTimeLag -= fDT;
			m_eCurDir = OBJECT_DIR::DOWN;

			if (m_fTimeLag <= 0 && m_eCurDir == m_ePastDir)
			{
				m_eCurMoveState = PLAYER_MOVE_STATE::MOVE;
			}
		}
		if (KEY_HOLD(KEY::LEFT) && m_ptBoardPos.x != 0)
		{
			m_fTimeLag -= fDT;
			m_eCurDir = OBJECT_DIR::LEFT;

			if (m_fTimeLag <= 0 && m_eCurDir == m_ePastDir)
			{
				m_eCurMoveState = PLAYER_MOVE_STATE::MOVE;
			}
		}
		if (KEY_HOLD(KEY::RIGHT) && m_ptBoardPos.x != BOARD_TILE - 1)
		{
			m_fTimeLag -= fDT;
			m_eCurDir = OBJECT_DIR::RIGHT;

			if (m_fTimeLag <= 0 && m_eCurDir == m_ePastDir)
			{
				m_eCurMoveState = PLAYER_MOVE_STATE::MOVE;
			}
		}

		// 키 입력 없을 때 타임 랙 재설정
		if (m_eCurDir != m_ePastDir)
		{
			m_fTimeLag = m_fTimeLagTerm;
		}
	}

	if (m_eCurMoveState == PLAYER_MOVE_STATE::IDLE || m_eCurMoveState == PLAYER_MOVE_STATE::MOVE)
	{
		if (KEY_TAP(KEY::X))
		{
			m_eCurAttackState = PLAER_ATTACK_STATE::SHOOT;
			CreateMissile();
		}
	}

	if (m_eCurAttackState == PLAER_ATTACK_STATE::SHOOT)
	{
		if (GetAnimator()->GetCurAnim()->IsFinish())
		{
			m_eCurAttackState = PLAER_ATTACK_STATE::IDLE;
		}
	}

	
}

void CPlayer::UpdateMove()
{
	if (m_eCurMoveState == PLAYER_MOVE_STATE::MOVE)
	{
		Vec2 curPos = GetPos();
		m_fMoveDelay -= fDT;
		if (m_fMoveDelay <= 0.0f)
		{
			m_fMoveDelay = 0.5f;
			switch (m_eCurDir)
			{
			case OBJECT_DIR::UP:
				m_ptBoardPos.y--;
				break;
			case OBJECT_DIR::LEFT:
				m_ptBoardPos.x--;
				break;
			case OBJECT_DIR::RIGHT:
				m_ptBoardPos.x++;
				break;
			case OBJECT_DIR::DOWN:
				m_ptBoardPos.y++;
				break;
			default:
				break;
			}
			curPos = Vec2{ (int)(m_ptBoardPos.x + 3) * BOARD_TILE + BOARD_TILE / 2, (int)m_ptBoardPos.y * BOARD_TILE + BOARD_TILE / 2 };
			SetPos(curPos);
			m_eCurMoveState = PLAYER_MOVE_STATE::IDLE;
		}
		// 0.2초 움직이고 0.3초 대기
		if (m_fMoveDelay >= 0.3f)
		{
			switch (m_eCurDir)
			{
			case OBJECT_DIR::UP:
				curPos.y -= m_fMoveMent * fDT * 5;
				break;
			case OBJECT_DIR::LEFT:
				curPos.x -= m_fMoveMent * fDT * 5;
				break;
			case OBJECT_DIR::RIGHT:
				curPos.x += m_fMoveMent * fDT * 5;
				break;
			case OBJECT_DIR::DOWN:
				curPos.y += m_fMoveMent * fDT * 5;
				break;
			default:
				break;
			}
		}
		SetPos(curPos);
	}
}

void CPlayer::UpdateAnimation()
{
	if (m_eCurAttackState != PLAER_ATTACK_STATE::IDLE)
	{
		switch (m_eCurAttackState)
		{
		case PLAER_ATTACK_STATE::SHOOT:
			GetAnimator()->Play(L"Shoot", false);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (m_eCurDir)
		{
		case OBJECT_DIR::UP:
			GetAnimator()->Play(L"IDLE_UP", true);
			break;
		case OBJECT_DIR::LEFT:
			GetAnimator()->Play(L"IDLE_LEFT", true);
			break;
		case OBJECT_DIR::RIGHT:
			GetAnimator()->Play(L"IDLE_RIGHT", true);
			break;
		case OBJECT_DIR::DOWN:
			GetAnimator()->Play(L"IDLE_DOWN", true);
			break;
		default:
			break;
		}
	}
}
