#pragma once


// ��� �귯���� ����� �����ϰ� ���� �� ������ �⺻ ��� �귯���� �ǵ��������� ���� Ŭ����
// ���� ������ �����ϰ� ���� �ش� �Լ��� ����Ǹ� ���� �������� �������鼭 �Ҹ��ڰ� �߻��ϸ鼭 �Ҹ��ڿ��� �⺻ �������� ��ȯ �� �����ȴ�.
class SelectGDI
{
private:
	HDC		m_hDC;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;

public:
	

public:
	SelectGDI(HDC _dc, PEN_TYPE _ePenType);
	SelectGDI(HDC _dc, BRUSH_TYPE _ePenType);
	~SelectGDI();
};

