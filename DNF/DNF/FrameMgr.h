#pragma once

class CFrame;
class CFrameMgr
{
	DECLARE_SINGLETON(CFrameMgr)
private:
	typedef map<const TCHAR*, shared_ptr<CFrame>>	MAPFRAME;
	MAPFRAME							m_mapFrame;
private:
	explicit	CFrameMgr(void);
private:
	shared_ptr<CFrame> Find_Frame(const TCHAR* pFrameTag);
public:
	HRESULT	Initialize_Frames(const TCHAR* pFrameTag, const _float& fLimitCall);
	_bool	Is_Call(const TCHAR* pFrameTag, const _float& fTimeDelta);
public:
	virtual ~CFrameMgr(void);
};