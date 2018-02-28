#include "stdafx.h"
#include "FontMgr.h"
#include "Font.h"

IMPLEMENT_SINGLETON(CFontMgr)

CFontMgr::CFontMgr(void)
{
}

HRESULT CFontMgr::Add_Font(const TCHAR * pFontKey, const _uint & iHeight, const _uint & iWidth, const _uint & iWeight)
{
	CFont*	pFont = CFont::Create(iHeight, iWidth, iWeight, pFontKey);
	NULL_CHECK_RETURN(pFont, E_FAIL);

	m_mapFont.insert(pair<const TCHAR*, auto_ptr<CFont>>(pFontKey, auto_ptr<CFont>(pFont)));

	return S_OK;
}

void CFontMgr::Render_Font(const TCHAR * pFontKey, const _vec3 & vPos, const TCHAR * pString, _color Color)
{
	m_mapFont[pFontKey]->Render_Font(pString, Color, vPos);
}

CFontMgr::~CFontMgr(void)
{
	m_mapFont.clear();
}
