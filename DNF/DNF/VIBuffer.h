#pragma once

#include "Resources.h"

class CVIBuffer : public CResources
{
public:
	enum BUFFERTYPE { BUFFER_RCTEX, BUFFER_END };
protected:
	explicit CVIBuffer(void);
	explicit CVIBuffer(const CVIBuffer& Prototype);	
protected:
	virtual HRESULT		Create_Buffer(void);
public:
	virtual CResources*	Clone_Resource(void) PURE;	
public:
	void Get_VtxInfo(void* pVertex);
	void Set_VtxInfo(void* pVertex);
	void Set_IdxInfo(void* pIdxInfo, const _ulong* pTriCnt);
	void Render_Buffer(const _matrix* pmatWorld);
protected:
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	_ulong					m_dwVtxSize;
	_ulong					m_dwVtxCnt;
	_ulong					m_dwVtxFVF;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	_ulong					m_dwIdxSize;
	_ulong					m_dwTriCnt;
	D3DFORMAT				m_IdxFmt = {};	
public:
	virtual ~CVIBuffer(void);
};