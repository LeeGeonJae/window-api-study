#include "pch.h"
#include "CScene.h"


CScene::CScene()
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
