#pragma once
#include "pch.h"

#include "CPlayer.h"

class CPlayer;

class CPlayerState
{
public:
	CPlayerState();
	virtual ~CPlayerState();
	const CPlayer* GetOwner()
	{
		return m_pOwner;
	}
	virtual void update(CPlayer& _cPlayer) = 0;
private:
	CPlayer* m_pOwner;
};
