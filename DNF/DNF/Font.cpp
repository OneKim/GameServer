#include "stdafx.h"
#include "Font.h"

CFont::CFont()
{
}

HRESULT CFont::Initialize_Font(const _uint & iHeight, const _uint & iWidth, const _uint & iWeight, const TCHAR * pFaceName)
{
	D3DXFONT_DESC		Font_Desc;
	ZeroMemory(&Font_Desc, sizeof(D3DXFONT_DESC));

	Font_Desc.Height = m_iHeight = iHeight;
	Font_Desc.Width = m_iWidth = iWidth;
	Font_Desc.Weight = iWeight;
	lstrcpy(Font_Desc.FaceName, pFaceName);
	Font_Desc.CharSet = HANGEUL_CHARSET;

	FAILED_CHECK(D3DXCreateFontIndirect(Engine::Get_GraphicDev(), &Font_Desc, &m_pFont));
	return S_OK;
}

void CFont::Render_Font(const TCHAR * pString, _color Color, const _vec3 & vPos)
{
	RECT	rc = { static_cast<_long>(vPos.x), static_cast<_long>(vPos.y)
					, static_cast<_long>(vPos.x + m_iWidth * lstrlen(pString)), static_cast<_long>(vPos.y + m_iHeight) };

	m_pFont->DrawTextW(NULL, pString, lstrlen(pString), &rc, DT_NOCLIP, Color);
}

CFont * CFont::Create(const _uint & iHeight, const _uint & iWidth, const _uint & iWeight, const TCHAR * pFaceName)
{
	CFont*		pFont = new CFont();
	if (FAILED(pFont->Initialize_Font(iHeight, iWidth, iWeight, pFaceName)))
		Safe_Delete(pFont);

	return pFont;
}

CFont::~CFont(void)
{
	Safe_Release(m_pFont);
}
