#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	:m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::Init()
{
	//\bin\content
	GetCurrentDirectory(255, m_szContentPath);

	SetWindowText(CCore::GetInst()->GetMainHWnd(), m_szContentPath);
}