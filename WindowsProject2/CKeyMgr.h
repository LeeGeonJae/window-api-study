#pragma once

enum KEY_STATE
{
	NONE,	// 눌리지 않았고, 이전에도 눌리지 않은 상태
	TAP,	// 막 누른 시점
	HOLD,	// 누르고 있는
	AWAY,	// 막 땐 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LBTN,
	RBTN,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE	eState;			// 키의 상태값
	bool		bPrevPush;		// 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }
	void SetMousePos(float _x, float _y) { Mouse_Pos.x = _x; Mouse_Pos.y = _y; }
	Vec2 GetMousePos() { return Mouse_Pos; }

private:
	vector<tKeyInfo> m_vecKey;
	Vec2 Mouse_Pos;

};