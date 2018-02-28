#pragma once

class CFont;
class CFontMgr
{
public:
	DECLARE_SINGLETON(CFontMgr)
private:
	map<const TCHAR*, auto_ptr<CFont>>			m_mapFont;
private:
	explicit	CFontMgr(void);
public:
	HRESULT	Add_Font(const TCHAR* pFontKey, const _uint& iHeight, const _uint& iWidth, const _uint& iWeight);
	void	Render_Font(const TCHAR* pFontKey, const _vec3& vPos, const TCHAR* pString, _color Color);
public:
	~CFontMgr(void);
};