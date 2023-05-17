#include "pch.h"
#include "CScene.h"

#include "CResMgr.h"
#include "CPathMgr.h"

#include "CObject.h"
#include "CTile.h"


CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); j++)
		{
			// m_arrObj[i] 그룹 백터의 j물체 삭제
			delete m_arrObj[i][j];
		}
	}
}

// 모든 오브젝트 update하기 단 Dead상태일 경우 EventMgr에서 다음 프레임에서 제거하기 때문에 그려주지 않는다
void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
       			if (!m_arrObj[i][j]->IsDead())
				m_arrObj[i][j]->update();
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}

// 모든 오브젝트 그려주기 단 Dead상태일 경우 EventMgr에서 다음 프레임에서 제거하기 때문에 그려주지 않는다
void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

// 모든 오브젝트 삭제하기
void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	//for (UINT i = 0; i < m_arrObj[(UINT)_eTarget].size(); i++)
	//{
	//	delete m_arrObj[(UINT)_eTarget][i];
	//}
	//m_arrObj[(UINT)_eTarget].clear();

	Safe_Delete_Vec<CObject*>
		(m_arrObj[(UINT)_eTarget]);
}

// 모든 오브젝트 삭제하기
void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}


// 타일 생성하기 함수 ( 추가 : 이건재 )
void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\Tile\\Tile1.bmp");

	// 타일 생성
	for (UINT i = 0; i < _iYCount; i++)
	{
		for (UINT j = 0; j < _iXCount; j++)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * BOARD_TILE), (float)(i * BOARD_TILE)));
			pTile->SetScale(Vec2(BOARD_TILE, BOARD_TILE));
			//pTile->SetScale(Vec2(32.f, 32.f));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

// 타일 불러오기 함수 ( 추가 : 이건재 )
void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 커널 오브젝트
	FILE* pFile = nullptr;

	// 세 번째 인자 w는 쓰기, r는 읽기, rb는 바이너리 모드로 읽겠다
	// 읽기 모드에서 해당 경로에 파일이 없을 경우에 nullptr 반환
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// 타일 가로 세로 개수 불러오기
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);


	// 불러온 개수에 맞게 EmptyTile 들 만들어두기
	CreateTile(xCount, yCount);

	// 만들어진 타일 개별로 필요한 정보를 불러오게 함
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		(((CTile*)vecTile[i])->Load(pFile));
	}

	fclose(pFile);
}
