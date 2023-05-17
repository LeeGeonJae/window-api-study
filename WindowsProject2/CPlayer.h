#pragma once
#include "CObject.h"
#include "CTexture.h"
#include "CPlayerState.h"

class CPlayerState;

enum class PLAYER_MOVE_STATE
{
	IDLE,
	MOVE,
};

enum class PLAER_ATTACK_STATE
{
	IDLE,
	SHOOT
};

class CPlayer :
	public CObject
{
private:
    // ���ҽ� ������ ���� �޾Ƽ� ��� �ϴ� ���̴� ���� �����ڸ� ������ �ʿ䰡 ����.
	float m_fMoveDelay;
	float m_fShootDelay;
	float m_fMoveMent;
	float m_fMoveTerm;

	float m_fTimeLag;
	const float m_fTimeLagTerm = 1.0f;

	OBJECT_DIR m_eCurDir;
	OBJECT_DIR m_ePastDir;
	bool m_bCanMove;

	POINT m_ptBoardPos;
	PLAYER_MOVE_STATE m_eCurMoveState;
	PLAYER_MOVE_STATE m_ePastMoveState;
	PLAER_ATTACK_STATE m_eCurAttackState;

	//CPlayerState* m_pState;

public:
	virtual void update();
	virtual void render(HDC _dc);
    virtual CPlayer* Clone() { return new CPlayer(*this); }

	void SetMovement(float _fMovement) { m_fMoveMent = _fMovement; };

	OBJECT_DIR GetDir() const
	{
		return m_eCurDir;
	}
	void SetDir(OBJECT_DIR val)
	{
		m_eCurDir = val;
	}
	POINT GetBoardPos() const
	{
		return m_ptBoardPos;
	}
	void SetBoardPos(POINT val)
	{
		m_ptBoardPos = val;
	}
private:
	void CreateMissile();
	void UpateState();
	void UpdateMove();
	void UpdateAnimation();

public:
	CPlayer();
	~CPlayer();
};