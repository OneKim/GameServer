#include "stdafx.h"
#include "Timer.h"

CTimer::CTimer(void)
	: m_fTimeDelta(0.f)
{	
}

HRESULT CTimer::Initialize_Timer(void)
{
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceFrequency(&m_CpuTime);

	return S_OK;
}

_float CTimer::Get_TimeDelta(void)
{
	return m_fTimeDelta;
}

void CTimer::Set_TimeDelta(void)
{
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_LastTime.QuadPart >= m_CpuTime.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTime);
		m_LastTime = m_FrameTime;
	}

	m_fTimeDelta = _float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTime.QuadPart;

	m_FixTime = m_FrameTime;
}

CTimer * CTimer::Create(void)
{
	CTimer* pInstance = new CTimer;

	if (FAILED(pInstance->Initialize_Timer()))
	{
		MSG_BOX(L"CTimer Created Failed");
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CTimer::~CTimer(void)
{

}
