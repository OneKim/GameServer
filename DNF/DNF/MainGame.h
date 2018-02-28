#pragma once

class CMainGame
{
private:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
private:
	TCHAR						m_szFPS[128] = {};
	_float						m_fAccTime;	
	_ushort						m_usNumRender;
private:
	explicit	CMainGame(void);
private:
	HRESULT	Initialize_MainGame(void);
	HRESULT Initialize_Resource(void);
public:
	void	Update(const _float& fTimeDelta);
	void	Render(void);
public:
	static CMainGame*	Create(void);
public:
	~CMainGame(void);
};