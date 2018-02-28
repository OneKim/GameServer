#include "stdafx.h"
#include "TimeMgr.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr(void)
{
}

HRESULT CTimeMgr::Initialize_Timers(const TCHAR * pTimerTag)
{
	NULL_CHECK_RETURN_MSG(!Find_Timer(pTimerTag), E_FAIL, L"Already SameTag Timer exist");

	m_mapTimers.insert(pair<const TCHAR*, shared_ptr<CTimer>>(pTimerTag, shared_ptr<CTimer>(CTimer::Create())));

	return  S_OK;
}

_float CTimeMgr::Get_TimeDelta(const TCHAR * pTimerTag)
{
	shared_ptr<CTimer> pTimer = Find_Timer(pTimerTag);

	if (NULL == pTimer)
		return 0.f;

	return pTimer->Get_TimeDelta();
}

void CTimeMgr::Set_TimeDelta(const TCHAR * pTimerTag)
{
	shared_ptr<CTimer> pTimer = Find_Timer(pTimerTag);

	if (NULL == pTimer)
		return;

	pTimer->Set_TimeDelta();
}

shared_ptr<CTimer> CTimeMgr::Find_Timer(const TCHAR * pTimerTag)
{
	MAPTIMERS::iterator	iter = find_if(m_mapTimers.begin(), m_mapTimers.end(), CTagFinder(pTimerTag));

	if(iter == m_mapTimers.end())
		return NULL;

	return iter->second;
}

CTimeMgr::~CTimeMgr(void)
{
	m_mapTimers.clear();
}