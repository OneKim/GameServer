#include "stdafx.h"
#include "Loading.h"

_bool CLoading::m_bLoad_StaticResources = false;

CLoading::CLoading(LOADINGTYPE eLoadType)
	: m_LoadType(eLoadType)
	, m_bComplete(false)
{
}

void CLoading::Initialize_Loading(void)
{
	InitializeCriticalSection(&m_CSKey);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Loading_Function, this, 0, NULL);
}

void CLoading::Loading_Logo(void)
{
	lstrcpy(m_szLoadMessage, L"로딩 완료...");

	m_bComplete = true;
}

void CLoading::Loading_SeriaRoom(void)
{
	lstrcpy(m_szLoadMessage, L"로딩 완료...");

	m_bComplete = true;
}

void CLoading::Loading_NobleSky(void)
{
	lstrcpy(m_szLoadMessage, L"로딩 완료...");

	m_bComplete = true;
}

void CLoading::Loading_StaticResources(void)
{
	if(true == m_bLoad_StaticResources)
		return;

	m_bLoad_StaticResources = true;
}

CLoading::LOADINGTYPE CLoading::Get_LoadType(void)
{
	return m_LoadType;
}

CRITICAL_SECTION * CLoading::Get_CSKey(void)
{
	return &m_CSKey;
}

const TCHAR * CLoading::Get_LoadMessage(void)
{
	return m_szLoadMessage;
}

const bool CLoading::Get_Complete(void)
{
	return m_bComplete;
}

CLoading * CLoading::Create(LOADINGTYPE eLoadType)
{
	CLoading* pLoading = new CLoading(eLoadType);
	pLoading->Initialize_Loading();

	return pLoading;
}

UINT CLoading::Loading_Function(void * pArg)
{
	CLoading*	pLoading = static_cast<CLoading*>(pArg);

	EnterCriticalSection(pLoading->Get_CSKey());

	pLoading->Loading_StaticResources();

	switch (pLoading->Get_LoadType())
	{
	case LOADING_LOGO:
		pLoading->Loading_Logo();
		break;
	case LOADING_SR:
		pLoading->Loading_SeriaRoom();
		break;
	case LOADING_NS:
		pLoading->Loading_NobleSky();
		break;
	}

	LeaveCriticalSection(pLoading->Get_CSKey());

	return 0;
}

const _bool CLoading::Is_LoadStatic(void)
{
	return m_bLoad_StaticResources;
}

CLoading::~CLoading(void)
{

}
