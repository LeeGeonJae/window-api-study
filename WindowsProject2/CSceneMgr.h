#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
public:
	void Init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];		// ¸ðµç ¾À ¸ñ·Ï
	CScene* m_pCurScene;							// ÇöÀç ¾À
};
