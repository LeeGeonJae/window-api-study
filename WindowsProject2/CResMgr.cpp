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

// 오브젝트 들에서 텍스쳐 파일을 로드할 때
// 해당 텍스쳐를 저장할 map의 key의 이름과
// _strRelativePath : content폴더의 다음 경로와 파일 이름
CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 현재 map에서 해당 텍스쳐 파일이 이미 로드된 상태라면 해당 텍스쳐 파일 반환
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	// PathMgr에서 경로를 찾아온다 strFilePath = L"Output\\bin\\content"
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	// strFilePath에서 다음 경로와 가져올 텍스쳐 파일의 이름을 매개변수로 받아왔기 때문에 추가해주면 된다.
	strFilePath += _strRelativePath;

	// 텍스쳐 객체의 메모리를 할당받고 
	// CTexture의 Load() 함수에서 이미지 파일 가져오고 Key와 상대경로 세팅
	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	// map에 Key와 해당 Texture의 주소 입력
	m_mapTex.insert(make_pair(_strKey, pTex));

	// 로드받은 Texture를 반환
	return pTex;
}

// map에 지정된 키에 Texture가 있는지 확인
CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}
