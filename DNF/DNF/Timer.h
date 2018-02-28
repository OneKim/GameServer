#pragma once

class CTimer
{
private:
	LARGE_INTEGER			m_FrameTime;
	LARGE_INTEGER			m_LastTime;
	LARGE_INTEGER			m_FixTime;
	LARGE_INTEGER			m_CpuTime;
	_float					m_fTimeDelta;
private:
	explicit	CTimer(void);	
public:
	HRESULT Initialize_Timer(void);
	_float	Get_TimeDelta(void);
	void	Set_TimeDelta(void);
public:
	static CTimer* Create(void);
public:
	~CTimer(void);
};