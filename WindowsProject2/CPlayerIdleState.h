#pragma once
#include "CPlayerState.h"
class CPlayerIdleState : public CPlayerState
{
public:
	virtual void update();
	virtual void render(HDC _dc);
};

