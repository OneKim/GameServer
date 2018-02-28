#pragma once

class CLoading
{
public:
	enum LOADINGTYPE { LOADING_LOGO, LOADING_SR, LOADING_NS, LOADING_END };
private:
	static _bool				m_bLoad_StaticResources;
private:
	LOADINGTYPE					m_LoadType;
	CRITICAL_SECTION			m_CSKey;
	HANDLE						m_hThread;
private:
	TCHAR						m_szLoadMessage[128] = {};
	_bool						m_bComplete;
private:
	explicit	CLoading(LOADINGTYPE eLoadType);
private:
	void Initialize_Loading(void);
	void Loading_Logo(void);
	void Loading_SeriaRoom(void);
	void Loading_NobleSky(void);
	void Loading_StaticResources(void);
public:
	LOADINGTYPE Get_LoadType(void);
	CRITICAL_SECTION* Get_CSKey(void);
	const TCHAR* Get_LoadMessage(void);
	const bool	 Get_Complete(void);	
public:
	static CLoading*	Create(LOADINGTYPE eLoadType);
	static UINT WINAPI	Loading_Function(void* pArg);
	static const _bool	Is_LoadStatic(void);
public:
	~CLoading(void);
};