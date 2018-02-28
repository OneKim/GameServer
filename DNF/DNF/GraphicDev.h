#pragma once

class CGraphicDev
{
public:
	DECLARE_SINGLETON(CGraphicDev)
public:
	enum WINMODE { MODE_FULL, MODE_WIN };
private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pDevice;
private:
	explicit CGraphicDev(void);
private:
	void Set_Parameters(D3DPRESENT_PARAMETERS& d3dpp, WINMODE Mode);	
public:
	HRESULT Initialize_GraphicDev(WINMODE Mode);
	LPDIRECT3DDEVICE9 Get_Device(void) { return m_pDevice; }
public:
	~CGraphicDev(void);
};