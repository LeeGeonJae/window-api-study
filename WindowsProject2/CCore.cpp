#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}

CCore::~CCore()
{
	// DC ��ȯ
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	// �� ����
	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// red Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}


// init ����
// 1. ������ �ڵ�� ������ ũ�⸦ ������ x, y��ǥ�� ���� POINT�� �Ű������� �޾ƿͼ� �����Ѵ�. 
// ( �̶� CCore�� Mgr Ŭ�������� �̹� �̱��� ���Ͽ��� static���� �����߱� ������,
//  ������ ������ �޸𸮰� ���� �ִ� ���¿��� ��ü�� ������ �ʿ䰡 ���� ���� ���� ������ ::GetInst()�� �ش� ��ü�� �ּҸ� ������ �� �ִ�. )
// 2. �ػ󵵿� �°� ������ ũ�� ����
// 3. ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����
// 4. ��Ʈ���� SelectObject�� �����Ѵ�
// 5. Manager �ʱ�ȭ
// 5-1. CPathMgr : ���ҽ� ������ ������ ��θ� wstring���� ����
// 5-2. CTimeMgr : �ð� ����
// 5-3. CKeyMgr : �Է� Ű ����
// 5-4. CSceneMgr : ������ ���� ����� ���� �� ����
// 5-5 CCollisionMgr : ����μ��� ����
int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr,100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// ���� ��� �� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	// ���� �߰��� ��� 
	// CSceneMgr�� Init�Լ��� �� �߰�!
	// define.h���� SCENE_TYPE �߰�!
	// CSene Ŭ������ �ڽ� Ŭ������ ���� �Ŀ� Enter()�Լ����� �ʿ� ��ġ�� ������Ʈ ����!
	// 
	// ������Ʈ�� �߰��� ���
	// ���࿡ ������Ʈ�� ���� ���� ��쿡 CObjectŬ������ �ڽ� Ŭ������ �����ϰ�
	// define.h���� GROUP_TYPE �߰�!
	// ������Ʈ �����ڿ��� ������Ʈ�� Collider�� Animation�� �ٿ��� �� �ֽ��ϴ�
	// ���� Collider�� �߰��� ��쿡 OnCollision�Լ�(3��)���� ����� �� �ֽ��ϴ�
	CSceneMgr::GetInst()->Init();
	CCollisionMgr::GetInst()->init();

	return S_OK;
}


// update ����
// 1. TimeMgr, KeyMgr
// 2. Scene update -> CurScene(���� ��)�� Object*->update
// 3. Scene fianlupdate -> CurScene(���� ��)�� Object*->finalupdate ����
// 4. Collision -> �ݸ��� �浹 üũ �� -> (�浹���� ���) Object*->OnCollision �Լ� ����
// 
// render ����
// 5. ȭ�� Ŭ����
// 6. Scene render -> CurScene(���� ��)�� Object*->render ����
// 7. BitBlt���� ���� ������ �ν��Ͻ��� HDC�� �׷��ش�
// 
// Event
// 8. EventMgr update -> Object���� �����ϰų�, �����ϰų�, CurScene(���� ��)�� ������ ���
void CCore::progress()
{
	// ==============
	// Manager Update
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	// =============
	// SCene Update
	// =============
	CSceneMgr::GetInst()->update();

	// �浹üũ
	CCollisionMgr::GetInst()->update();

	// =========
	// Rendering
	// =========
	// ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// =============
	// �̺�Ʈ ����ó��
	// =============
	CEventMgr::GetInst()->update();

}



