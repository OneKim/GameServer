#pragma once

class CTimer;
class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)
private:
	typedef map<const TCHAR*, shared_ptr<CTimer>>	MAPTIMERS;
	MAPTIMERS			m_mapTimers;
private:
	explicit	CTimeMgr(void);	
public:
	HRESULT Initialize_Timers(const TCHAR* pTimerTag);
	_float	Get_TimeDelta(const TCHAR* pTimerTag);
	void	Set_TimeDelta(const TCHAR* pTimerTag);
	shared_ptr<CTimer> Find_Timer(const TCHAR* pTimerTag);
public:
	~CTimeMgr(void);
};