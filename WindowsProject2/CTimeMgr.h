#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

private:
	LARGE_INTEGER	m_llcurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;	// ������ ������ �ð���
	double			m_dAcc;	// 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;	// �Լ� ȣ�� Ƚ�� üũ
	UINT			m_iFPS;		//�ʴ� ȣ�� Ƚ��
};