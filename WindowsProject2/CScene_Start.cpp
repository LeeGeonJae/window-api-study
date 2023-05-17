#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CBoard.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	// �θ��� update()�Լ��� ȣ��
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		// �̺�Ʈ ���
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

// ������Ʈ ����
void CScene_Start::Enter()
{	// Object �߰�

	// ��׶��� ������Ʈ
	CBoard* pBoard = nullptr;
	for (int i = 0; i < BOARD_SIZE_COL; i++)
	{
		for (int j = 0; j < BOARD_SIZE_ROW; j++)
		{
			pBoard = new CBoard;
			pBoard->SetName(L"Board");
			pBoard->SetPos(Vec2{ BOARD_TILE * (i + BOARD_PENDING), BOARD_TILE * j });
			pBoard->SetScale(Vec2{ BOARD_TILE, BOARD_TILE });
			AddObject(pBoard, GROUP_TYPE::DEFAULT);
		}
	}

	// �÷��̾� �߰�
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2{ (BOARD_TILE / 2) + (BOARD_TILE * 3), BOARD_TILE / 2});
	pObj->SetScale(Vec2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 0 ,0 });
	AddObject(pObj, GROUP_TYPE::PLAYER);




	//CObject* pOtherPlayer = pObj->Clone();
		//pObj->SetPos(Vec2(740.f, 384.f));
		//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);
	// 	// ���� ��ġ
	// 	int iMonCount = 0;
	// 	float fMoveDist = 25.f;
	// 	float fObjScale = 50.f;
	// 
	// 	Vec2 vResoultion = CCore::GetInst()->GetResolution();
	// 
	// 	// ���� ���� ����
	// 	float fTerm = (vResoultion.x - ((fMoveDist + fObjScale / 2.f) * 2)) / (float)(iMonCount - 1);
	// 
	// 	CMonster* pMonsterObj = nullptr;
	// 
	// 	for (int i = 0; i < iMonCount; i++)
	// 	{
	// 		pMonsterObj = new CMonster;
	// 		pMonsterObj->SetName(L"Monster");
	// 		pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2.f) + fTerm * (float)i, 50.f));
	// 		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
	// 		pMonsterObj->SetMoveDistance(fMoveDist);
	// 		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
	// 		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	// 	}


	// Ÿ�� �ε�
	//LoadTile(L"Tile\\Start.tile");

	// �浹 ��Ʈ���� ���� ( �浹�ؾ��� �� ��ü�� üũ, üũ���� ������ ���ĵ� �浹���� �ʴ´�. )
	// Player �׷�� Monster �׷� ���� �浹üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
}

void CScene_Start::Exit()
{
	// ��� ������Ʈ ����
	DeleteAll();

	// �浹 ��Ʈ���� üũ ����
	CCollisionMgr::GetInst()->Reset();
}
