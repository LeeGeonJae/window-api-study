#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	//for (map<wstring, CTexture*>::iterator iter = m_mapTex.begin(); iter != m_mapTex.end(); iter++)
	//{
	//	delete iter->second;
	//}
	// m_mapTex.clear();

	Safe_Delete_map(m_mapTex);
}

// ������Ʈ �鿡�� �ؽ��� ������ �ε��� ��
// �ش� �ؽ��ĸ� ������ map�� key�� �̸���
// _strRelativePath : content������ ���� ��ο� ���� �̸�
CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// ���� map���� �ش� �ؽ��� ������ �̹� �ε�� ���¶�� �ش� �ؽ��� ���� ��ȯ
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	// PathMgr���� ��θ� ã�ƿ´� strFilePath = L"Output\\bin\\content"
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	// strFilePath���� ���� ��ο� ������ �ؽ��� ������ �̸��� �Ű������� �޾ƿԱ� ������ �߰����ָ� �ȴ�.
	strFilePath += _strRelativePath;

	// �ؽ��� ��ü�� �޸𸮸� �Ҵ�ް� 
	// CTexture�� Load() �Լ����� �̹��� ���� �������� Key�� ����� ����
	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	// map�� Key�� �ش� Texture�� �ּ� �Է�
	m_mapTex.insert(make_pair(_strKey, pTex));

	// �ε���� Texture�� ��ȯ
	return pTex;
}

// map�� ������ Ű�� Texture�� �ִ��� Ȯ��
CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}
