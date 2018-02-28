#include "stdafx.h"
#include "Texture.h"

CTexture::CTexture(void)
{
}

CTexture::CTexture(const CTexture & Prototype)
	: CResources(Prototype)
	, m_dwContainerSize(Prototype.m_dwContainerSize)
{
	m_vecTexture = Prototype.m_vecTexture;

	size_t iSize = m_vecTexture.size();

	for (size_t i = 0; i < iSize; ++i)
		m_vecTexture[i]->AddRef();
}

CResources * CTexture::Clone_Resource(void)
{
	return new CTexture(*this);
}

IDirect3DBaseTexture9* CTexture::Get_Texture(const _ulong dwIndex)
{
	if (m_dwContainerSize <= dwIndex || dwIndex < 0)
		return NULL;

	return m_vecTexture[dwIndex];
}

_ulong CTexture::Get_ContainerSize(void)
{
	return m_dwContainerSize;
}

void CTexture::Set_ConstantTable(LPD3DXEFFECT pEffect, const char * pConstantName, const _uint & iCnt)
{
	pEffect->SetTexture(pConstantName, m_vecTexture[iCnt]);
}

HRESULT CTexture::Load_Texture(const TCHAR * pFilePath, const _ushort & wCnt)
{
	IDirect3DBaseTexture9*		pTexture = NULL;

	if (wCnt == 0)
		return E_FAIL;

	TCHAR		szFullPath[MAX_PATH] = L"";

	for (size_t i = 0; i < wCnt; ++i)
	{
		wsprintf(szFullPath, pFilePath, i);

		FAILED_CHECK_MSG(D3DXCreateTextureFromFile(m_pGraphicDev, szFullPath, (LPDIRECT3DTEXTURE9*)&pTexture), L"Texture Create From File Failed");

		m_vecTexture.push_back(pTexture);
	}

	m_dwContainerSize = m_vecTexture.size();

	return S_OK;
}

void CTexture::Render_Texture(const _ulong& iIndex, const _ulong& dwStage /*= 0*/)
{
	if (iIndex >= m_dwContainerSize)
		return;

	m_pGraphicDev->SetTexture(dwStage, m_vecTexture[iIndex]);
}

CTexture * CTexture::Create(const TCHAR * pFilePath, const _ushort & wCnt)
{
	CTexture*	pInstance = new CTexture();
	if (FAILED(pInstance->Load_Texture(pFilePath, wCnt)))
	{
		MSG_BOX(L"pFilePath");
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CTexture::~CTexture(void)
{
	for_each(m_vecTexture.begin(), m_vecTexture.end(), CRelease_Single());
	m_vecTexture.clear();
}
