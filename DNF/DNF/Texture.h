#pragma once

#include "Resources.h"

class CTexture : public CResources
{
private:
	typedef vector<IDirect3DBaseTexture9*>	VECTEXTURE;
	VECTEXTURE	m_vecTexture;
	_ulong		m_dwContainerSize;
private:
	explicit	CTexture(void);
	explicit	CTexture(const CTexture& Prototype);
public:
	virtual CResources* Clone_Resource(void);	
public:
	IDirect3DBaseTexture9*	Get_Texture(const _ulong dwIndex = 0);
	_ulong					Get_ContainerSize(void);
	void					Set_ConstantTable(LPD3DXEFFECT pEffect, const char* pConstantName, const _uint& iCnt = 0);
public:
	HRESULT	Load_Texture(const TCHAR* pFilePath, const _ushort& wCnt);
	void	Render_Texture(const _ulong& iIndex, const _ulong& dwStage = 0);
public:
	static CTexture* Create(const TCHAR* pFilePath, const _ushort& wCnt);
public:
	virtual ~CTexture(void);
};