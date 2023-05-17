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
	// \bin\content
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = (int)wcslen(m_szContentPath);

	// ���� ������
	// Debug�� ������ ��쿡�� \\Output\\bin.Debug�� ����Ǵ�
	// \\Output ���� �����ϱ� ����
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// \\Output\\bin\\content�� ���ڿ� �Է�
	// ������ ���ҽ� texture�� sound�� ���еǾ� �ִµ� �̴� �� ������Ʈ���� �����Ѵ�
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	SetWindowText(CCore::GetInst()->GetMainHWnd(), m_szContentPath);
}