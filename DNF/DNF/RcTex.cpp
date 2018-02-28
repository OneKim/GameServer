#include "stdafx.h"
#include "RcTex.h"

CRcTex::CRcTex(void)
{
}

CRcTex::CRcTex(const CRcTex & Prototype)
	: CVIBuffer(Prototype)
{
}

CResources * CRcTex::Clone_Resource(void)
{
	return new CRcTex(*this);
}

HRESULT CRcTex::Create_Buffer(void)
{
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = 4;
	m_dwVtxFVF = VTXFVF_TEX;

	m_dwIdxSize = sizeof(INDEX16);
	m_dwTriCnt = 2;
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::Create_Buffer());

	VTXTEX*			pVtxTex = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtxTex, 0);

	pVtxTex[0].vPos = _vec3(-0.5f, 0.5f, 0.f);
	pVtxTex[0].vNormal = _vec3(0.f, 0.f, -1.f);
	pVtxTex[0].vTexUV = _vec2(0.f, 0.f);

	pVtxTex[1].vPos = _vec3(0.5f, 0.5f, 0.f);
	pVtxTex[1].vNormal = _vec3(0.f, 0.f, -1.f);
	pVtxTex[1].vTexUV = _vec2(1.f, 0.f);

	pVtxTex[2].vPos = _vec3(0.5f, -0.5f, 0.f);
	pVtxTex[2].vNormal = _vec3(0.f, 0.f, -1.f);
	pVtxTex[2].vTexUV = _vec2(1.f, 1.f);

	pVtxTex[3].vPos = _vec3(-0.5f, -0.5f, 0.f);
	pVtxTex[3].vNormal = _vec3(0.f, 0.f, -1.f);
	pVtxTex[3].vTexUV = _vec2(0.f, 1.f);

	m_pVB->Unlock();

	INDEX16*			pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3;

	m_pIB->Unlock();

	return S_OK;
}

CRcTex * CRcTex::Create(void)
{
	CRcTex* pInstance = new CRcTex;

	if (FAILED(pInstance->Create_Buffer()))
	{
		MSG_BOX(L"CRcTex Created Failed");
		Safe_Delete(pInstance);
	}

	return pInstance;
}

CRcTex::~CRcTex(void)
{
}
