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
			// m_arrObj[i] �׷� ������ j��ü ����
			delete m_arrObj[i][j];
		}
	}
}
