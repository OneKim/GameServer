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

	m_mapFont.insert(pair<const TCHAR*, CFont*>(pFontKey, pFont));

	return S_OK;
}

void CFontMgr::Render_Font(const TCHAR * pFontKey, const _vec3 & vPos, const TCHAR * pString, _color Color)
{
	map<const TCHAR*, CFont*>::iterator	iter = find_if(m_mapFont.begin(), m_mapFont.end(), CTagFinder(pFontKey));

	if (iter == m_mapFont.end())
		return;

	iter->second->Render_Font(pString, Color, vPos);
}

CFontMgr::~CFontMgr(void)
{
	for (auto font : m_mapFont)
		Safe_Delete(font.second);

	m_mapFont.clear();
}
