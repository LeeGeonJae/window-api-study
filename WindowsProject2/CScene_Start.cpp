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
	// 부모쪽 update()함수를 호출
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		// 이벤트 등록
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

// 오브젝트 세팅
void CScene_Start::Enter()
{	// Object 추가

	// 백그라운드 오브젝트
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

	// 플레이어 추가
	CPlayer* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2{ (BOARD_TILE / 2) + (BOARD_TILE * 3), BOARD_TILE / 2});
	pObj->SetScale(Vec2(100.f, 100.f));
	pObj->SetBoardPos(POINT{ 0 ,0 });
	AddObject(pObj, GROUP_TYPE::PLAYER);




	//CObject* pOtherPlayer = pObj->Clone();
		//pObj->SetPos(Vec2(740.f, 384.f));
		//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);
	// 	// 몬스터 배치
	// 	int iMonCount = 0;
	// 	float fMoveDist = 25.f;
	// 	float fObjScale = 50.f;
	// 
	// 	Vec2 vResoultion = CCore::GetInst()->GetResolution();
	// 
	// 	// 몬스터 사이 간격
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


	// 타일 로딩
	//LoadTile(L"Tile\\Start.tile");

	// 충돌 매트릭스 지정 ( 충돌해야할 두 객체를 체크, 체크하지 않으면 겹쳐도 충돌하지 않는다. )
	// Player 그룹과 Monster 그룹 간의 충돌체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
}

void CScene_Start::Exit()
{
	// 모든 오브젝트 삭제
	DeleteAll();

	// 충돌 매트릭스 체크 해제
	CCollisionMgr::GetInst()->Reset();
}
