#pragma once

// Mgr 클래스들은 프로그램이 실행되는 동안에 하나만 존재해야 하기 때문에
// 싱글톤 패턴을 쓰기 쉽게 전처리기로 만들어 두었습니다
#define SINGLE(type) public:\
					 static type* GetInst()\
					{\
						static type mgr;\
						return &mgr;\
					}\
					 private:\
						type(); \
						~type();

// 시간 함수입니다.
// float m_fAccTime += fDT;
// static int Second = 0;
// if ( m_fAccTime >= 1.f)
// {
//		Second++;				// 1초씩 늘어남
//		m_fAccTime - 1.f;
// }
// 이런 식으로 사용할 수 있습니다.
#define DT CTimeMgr::GetInst()->GetDT()
#define fDT CTimeMgr::GetInst()->GetfDT()

//클론함수를 매크로 바꾸어 두었습니다.
#define CLONE(type) type * Clone() {return new type (*this);}

// 키의 상태를 쓰기 쉽게 전처리기로 만들어 두었습니다.
#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

// 원형의 파이 입니다
#define PI -3.1415926535

#define BOARD_TILE 120
#define BOARD_SIZE_COL 13
#define BOARD_SIZE_ROW 9
#define BOARD_PENDING 3


// Object 타입입니다. 
// Object 를 추가할 경우에 여기에 Type도 추가해주어야 합니다.
enum class GROUP_TYPE
{
	DEFAULT,			// 기본
	TILE,				// 타일 ( 추가 : 이건재 )
	PLAYER,				// 플레이어
	MONSTER,			// 몬스터
	PROJ_PLAYER,		// 플레이어가 쏜 미사일
	PROJ_MONSTER,		// 몬스터가 쏜 미사일

	UI  = 31,
	END = 32,
};

// Scene 타입입니다.
// Scene 을 추가할 경우에 여기에 Type도 추가해주어야 합니다.
enum class SCENE_TYPE
{
	TOOL,				// 툴 맵
	START,				// 스타트 맵
	
	STAGE_01,			// 스테이지 1 맵
	STAGE_02,			// 스테이지 2 맵

	END,
};

// 브러쉬 타입입니다.
enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

// 펜 타입입니다
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	END,
};

// 이벤트 타입입니다.
// 이벤트를 추가할 경우에 여기에 TYPE도 추가해 주어야 합니다.
enum class EVENT_TYPE
{
	CREATE_OBJECT,		// 오브젝트 생성될 때,
	DELETE_OBJECT,		// 오브젝트 삭제될 때
	SCENE_CHANGE,		// 씬이 종료될 때


	END
};

enum class OBJECT_DIR
{
	UP,
	LEFT,
	RIGHT,
	DOWN
};

