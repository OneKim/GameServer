#pragma once

class CFrame
{
private:
	_float				m_fLimitCall;
	_float				m_fAccTime;
private:
	explicit	CFrame(void);
public:
	HRESULT	Initialize_Frame(const _float& fLimitCall);
	_bool	Is_Call(const _float& fTimeDelta);	
public:
	static CFrame* Create(const _float& fLimitCall);
public:
	~CFrame(void);
};