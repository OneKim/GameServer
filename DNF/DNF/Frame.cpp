#include "stdafx.h"
#include "Frame.h"

CFrame::CFrame(void)
	: m_fLimitCall(0.f)
	, m_fAccTime(0.f)
{
}

HRESULT CFrame::Initialize_Frame(const _float & fLimitCall)
{
	m_fLimitCall = 1.f / fLimitCall;

	return S_OK;
}

_bool CFrame::Is_Call(const _float & fTimeDelta)
{
	m_fAccTime += fTimeDelta;

	if (m_fAccTime >= m_fLimitCall)
	{
		m_fAccTime = 0.f;
		return true;
	}
	return false;
}

CFrame * CFrame::Create(const _float & fLimitCall)
{
	CFrame* pInstance = new CFrame;

	if (FAILED(pInstance->Initialize_Frame(fLimitCall)))
	{
		MSG_BOX(L"CFrame Created Failed");
		Safe_Delete(pInstance);
	}

	return pInstance;
}

CFrame::~CFrame(void)
{

}
