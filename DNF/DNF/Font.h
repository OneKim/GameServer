#pragma once

class CFont
{
private:	
	LPD3DXFONT				m_pFont;
	_uint					m_iHeight;
	_uint					m_iWidth;
private:
	explicit CFont(void);
public:
	HRESULT	Initialize_Font(  const _uint& iHeight
							, const _uint& iWidth
							, const _uint& iWeight
							, const TCHAR* pFaceName);
	void	Render_Font(const TCHAR* pString, _color Color, const _vec3& vPos);
public:
	static CFont* Create( const _uint& iHeight
						, const _uint& iWidth
						, const _uint& iWeight
						, const TCHAR* pFaceName);
public:
	~CFont(void);
};