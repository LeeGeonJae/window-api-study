#pragma once

// Mgr Ŭ�������� ���α׷��� ����Ǵ� ���ȿ� �ϳ��� �����ؾ� �ϱ� ������
// �̱��� ������ ���� ���� ��ó����� ����� �ξ����ϴ�
#define SINGLE(type) public:\
					 static type* GetInst()\
					{\
						static type mgr;\
						return &mgr;\
					}\
					 private:\
						type(); \
						~type();

// �ð� �Լ��Դϴ�.
// float m_fAccTime += fDT;
// static int Second = 0;
// if ( m_fAccTime >= 1.f)
// {
//		Second++;				// 1�ʾ� �þ
//		m_fAccTime - 1.f;
// }
// �̷� ������ ����� �� �ֽ��ϴ�.
#define DT CTimeMgr::GetInst()->GetDT()
#define fDT CTimeMgr::GetInst()->GetfDT()

//Ŭ���Լ��� ��ũ�� �ٲپ� �ξ����ϴ�.
#define CLONE(type) type * Clone() {return new type (*this);}

// Ű�� ���¸� ���� ���� ��ó����� ����� �ξ����ϴ�.
#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

// ������ ���� �Դϴ�
#define PI -3.1415926535

#define BOARD_TILE 120
#define BOARD_SIZE_COL 13
#define BOARD_SIZE_ROW 9
#define BOARD_PENDING 3


// Object Ÿ���Դϴ�. 
// Object �� �߰��� ��쿡 ���⿡ Type�� �߰����־�� �մϴ�.
enum class GROUP_TYPE
{
	DEFAULT,			// �⺻
	TILE,				// Ÿ�� ( �߰� : �̰��� )
	PLAYER,				// �÷��̾�
	MONSTER,			// ����
	PROJ_PLAYER,		// �÷��̾ �� �̻���
	PROJ_MONSTER,		// ���Ͱ� �� �̻���

	UI  = 31,
	END = 32,
};

// Scene Ÿ���Դϴ�.
// Scene �� �߰��� ��쿡 ���⿡ Type�� �߰����־�� �մϴ�.
enum class SCENE_TYPE
{
	TOOL,				// �� ��
	START,				// ��ŸƮ ��
	
	STAGE_01,			// �������� 1 ��
	STAGE_02,			// �������� 2 ��

	END,
};

// �귯�� Ÿ���Դϴ�.
enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

// �� Ÿ���Դϴ�
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	END,
};

// �̺�Ʈ Ÿ���Դϴ�.
// �̺�Ʈ�� �߰��� ��쿡 ���⿡ TYPE�� �߰��� �־�� �մϴ�.
enum class EVENT_TYPE
{
	CREATE_OBJECT,		// ������Ʈ ������ ��,
	DELETE_OBJECT,		// ������Ʈ ������ ��
	SCENE_CHANGE,		// ���� ����� ��


	END
};

enum class OBJECT_DIR
{
	UP,
	LEFT,
	RIGHT,
	DOWN
};

