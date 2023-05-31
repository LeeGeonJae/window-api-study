#pragma once
#include "pch.h"
#include "CPlayerState.h"

class CPlayerMovingState : public CPlayerState
{
public:
	CPlayerMovingState();
	virtual ~CPlayerMovingState();
	virtual void update();
	virtual void render(HDC _dc);
	virtual void Enter();
	virtual void Exit();
};

