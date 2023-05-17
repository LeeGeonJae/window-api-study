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
			// m_arrObj[i] �׷� ������ j��ü ����
			delete m_arrObj[i][j];
		}
	}
}

// ��� ������Ʈ update�ϱ� �� Dead������ ��� EventMgr���� ���� �����ӿ��� �����ϱ� ������ �׷����� �ʴ´�
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

// ��� ������Ʈ �׷��ֱ� �� Dead������ ��� EventMgr���� ���� �����ӿ��� �����ϱ� ������ �׷����� �ʴ´�
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

// ��� ������Ʈ �����ϱ�
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

// ��� ������Ʈ �����ϱ�
void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}


// Ÿ�� �����ϱ� �Լ� ( �߰� : �̰��� )
void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\Tile\\Tile1.bmp");

	// Ÿ�� ����
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

// Ÿ�� �ҷ����� �Լ� ( �߰� : �̰��� )
void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// Ŀ�� ������Ʈ
	FILE* pFile = nullptr;

	// �� ��° ���� w�� ����, r�� �б�, rb�� ���̳ʸ� ���� �аڴ�
	// �б� ��忡�� �ش� ��ο� ������ ���� ��쿡 nullptr ��ȯ
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// Ÿ�� ���� ���� ���� �ҷ�����
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);


	// �ҷ��� ������ �°� EmptyTile �� �����α�
	CreateTile(xCount, yCount);

	// ������� Ÿ�� ������ �ʿ��� ������ �ҷ����� ��
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		(((CTile*)vecTile[i])->Load(pFile));
	}

	fclose(pFile);
}
