#pragma once
class CRes
{
private:
	wstring m_strKey;				// 리소스 키
	wstring m_strRelativePath;		// 리소스 상대경로

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strRelativePath) { m_strRelativePath = _strRelativePath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }
	HDC m_dc;
public:
	CRes(HDC _dc);
	virtual ~CRes();
};