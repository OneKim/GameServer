#pragma once

/////////////////////////////////////////////////////////////
//싱글톤
#define NO_COPY(CLASSNAME)									\
	private:												\
	CLASSNAME(const CLASSNAME&);							\
	CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)						\
	NO_COPY(CLASSNAME)										\
	private:												\
	static shared_ptr<CLASSNAME>	m_pInstance;			\
	public:													\
	static shared_ptr<CLASSNAME>	Get_Instance(void);		\

#define IMPLEMENT_SINGLETON(CLASSNAME)						\
	shared_ptr<CLASSNAME>	CLASSNAME::m_pInstance = NULL;	\
	shared_ptr<CLASSNAME>	CLASSNAME::Get_Instance(void) {	\
		if(NULL == m_pInstance) {							\
	m_pInstance = shared_ptr<CLASSNAME>(new CLASSNAME);		\
		}													\
		return m_pInstance;									\
	}

/////////////////////////////////////////////////////////////
//메세지박스
#define MSG_BOX(_message)			MessageBox(NULL, _message, L"System Message", MB_OK)
#define TAGMSG_BOX(_tag,_message)	MessageBox(NULL, _message, _tag, MB_OK)

#ifdef _WIN64
#define BREAK_POINT		__debugbreak()
#else
#define BREAK_POINT		__asm { int 3 }
#endif

/////////////////////////////////////////////////////////////
//널체크
#define NULL_CHECK( _ptr)	\
{if( _ptr == 0){BREAK_POINT;return;}}

#define NULL_CHECK_RETURN( _ptr, _return)	\
{if( _ptr == 0){BREAK_POINT;return _return;}}

#define NULL_CHECK_MSG( _ptr, _message )		\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);BREAK_POINT;}}

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);BREAK_POINT;return _return;}}

#define NULL_CHECK_RETURN_TAGMSG( _ptr, _return, _tag, _message )	\
{if( _ptr == 0){MessageBox(NULL, _message, _tag, MB_OK);BREAK_POINT;return _return;}}

/////////////////////////////////////////////////////////////
//FAILED체크
#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, L"Failed", L"System Error",MB_OK); BREAK_POINT; return E_FAIL;}

#define FAILED_CHECK_RETURN(_hr, _return)	if( ((HRESULT)(_hr)) < 0 )		\
{ MessageBox(NULL, L"Failed", L"System Error",MB_OK); BREAK_POINT; return _return;}

#define FAILED_CHECK_MSG( _hr, _message)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, _message, L"System Message",MB_OK); BREAK_POINT;return E_FAIL;}

#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, _message, L"System Message",MB_OK); BREAK_POINT;return _return;}