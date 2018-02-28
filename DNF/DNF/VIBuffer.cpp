#include "stdafx.h"
#include "VIBuffer.h"

CVIBuffer::CVIBuffer(void)
	: m_pVB(NULL)
	, m_dwVtxSize(0)
	, m_dwVtxCnt(0)
	, m_dwVtxFVF(0)
	, m_pIB(NULL)
	, m_dwIdxSize(0)
	, m_dwTriCnt(0)	
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & Prototype)
	: CResources(Prototype)
	, m_pVB(Prototype.m_pVB)
	, m_dwVtxSize(Prototype.m_dwVtxSize)
	, m_dwVtxCnt(Prototype.m_dwVtxCnt)
	, m_dwVtxFVF(Prototype.m_dwVtxFVF)
	, m_pIB(Prototype.m_pIB)
	, m_dwIdxSize(Prototype.m_dwIdxSize)
	, m_dwTriCnt(Prototype.m_dwTriCnt)
	, m_IdxFmt(Prototype.m_IdxFmt)
{
	m_pVB->AddRef();
	m_pIB->AddRef();
}

HRESULT CVIBuffer::Create_Buffer(void)
{
	FAILED_CHECK_MSG(m_pGraphicDev->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, 0, m_dwVtxFVF, D3DPOOL_MANAGED, &m_pVB, NULL), L"VertexBuffer Create Failed");
	FAILED_CHECK_MSG(m_pGraphicDev->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 0, m_IdxFmt, D3DPOOL_MANAGED, &m_pIB, NULL), L"IndexBuffer Create Failed");

	return S_OK;
}

void CVIBuffer::Get_VtxInfo(void * pVertex)
{
	void*	pOriVtx = NULL;

	m_pVB->Lock(0, 0, (void**)&pOriVtx, 0);
	memcpy(pVertex, pOriVtx, m_dwVtxSize * m_dwVtxCnt);
	m_pVB->Unlock();
}

void CVIBuffer::Set_VtxInfo(void * pVertex)
{
	void*	pOriVtx = NULL;

	m_pVB->Lock(0, 0, (void**)&pOriVtx, 0);
	memcpy(pOriVtx, pVertex, m_dwVtxSize * m_dwVtxCnt);
	m_pVB->Unlock();
}

void CVIBuffer::Set_IdxInfo(void * pIdxInfo, const _ulong * pTriCnt)
{
	void*	pOriIndex = NULL;

	m_dwTriCnt = *pTriCnt;

	m_pIB->Lock(0, 0, &pOriIndex, 0);
	memcpy(pOriIndex, pIdxInfo, m_dwIdxSize * m_dwTriCnt);
	m_pIB->Unlock();
}

void CVIBuffer::Render_Buffer(const _matrix * pmatWorld)
{
	if(NULL != pmatWorld)
		m_pGraphicDev->SetTransform(D3DTS_WORLD, pmatWorld);

	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	m_pGraphicDev->SetFVF(m_dwVtxFVF);
	m_pGraphicDev->SetIndices(m_pIB);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
}

CVIBuffer::~CVIBuffer(void)
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}
