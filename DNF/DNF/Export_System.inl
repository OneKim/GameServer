/////////////////////////////////////////////////////////////
//For.GraphicDev

//For.Getter
LPDIRECT3DDEVICE9 Engine::Get_GraphicDev(void)
{
	return CGraphicDev::Get_Instance()->Get_Device();
}

//For.Setter

//For.General
HRESULT Engine::Initialize_GraphicDev(CGraphicDev::WINMODE Mode)
{
	return CGraphicDev::Get_Instance()->Initialize_GraphicDev(Mode);
}

/////////////////////////////////////////////////////////////
//For.Input

//For.Getter
_ubyte Engine::Get_DIKeyState(_ubyte KeyFlag)
{
	return CInput::Get_Instance()->Get_DIKeyState(KeyFlag);
}

_ubyte Engine::Get_DIMouseState(CInput::MOUSEBTCLICK KeyFlag)
{
	return CInput::Get_Instance()->Get_DIMouseState(KeyFlag);
}

_long Engine::Get_DIMouseMove(CInput::MOUSEMOVE KeyFlag)
{
	return CInput::Get_Instance()->Get_DIMouseMove(KeyFlag);
}

_bool Engine::Get_DIKeyIsDown(_ubyte KeyFlag)
{
	return CInput::Get_Instance()->Get_KeyDown(KeyFlag);
}

_bool Engine::Get_DIKeyIsUp(_ubyte KeyFlag)
{
	return CInput::Get_Instance()->Get_KeyUp(KeyFlag);
}

_bool Engine::Get_DIMouseDown(CInput::MOUSEBTCLICK KeyFlag)
{
	return CInput::Get_Instance()->Get_MouseDown(KeyFlag);
}

_bool Engine::Get_DIMouseUp(CInput::MOUSEBTCLICK KeyFlag)
{
	return CInput::Get_Instance()->Get_MouseUp(KeyFlag);
}

//For.Setter
void Engine::Set_InputState(void)
{
	CInput::Get_Instance()->Set_InputState();
}

//For.General
HRESULT Engine::Initialize_InputDevice()
{
	return CInput::Get_Instance()->Initialize_InputDevice();
}

/////////////////////////////////////////////////////////////
//For.Font

//For.Getter

//For.Setter

//For.General
HRESULT Engine::Add_Font(const TCHAR * pFontKey, const _uint & iHeight, const _uint & iWidth, const _uint & iWeight)
{
	return CFontMgr::Get_Instance()->Add_Font(pFontKey, iHeight, iWidth, iWeight);
}

void Engine::Render_Font(const TCHAR * pFontKey, const _vec3 & vPos, const TCHAR * pString, _color Color)
{
	CFontMgr::Get_Instance()->Render_Font(pFontKey, vPos, pString, Color);
}

/////////////////////////////////////////////////////////////
//For.Timer

//For.Getter
_float Engine::Get_TimeDelta(const TCHAR * pTimerTag)
{
	return CTimeMgr::Get_Instance()->Get_TimeDelta(pTimerTag);
}

//For.Setter
void Engine::Set_TimeDelta(const TCHAR * pTimerTag)
{
	CTimeMgr::Get_Instance()->Set_TimeDelta(pTimerTag);
}

//For.General
HRESULT Engine::Initialize_Timers(const TCHAR * pTimerTag)
{
	return CTimeMgr::Get_Instance()->Initialize_Timers(pTimerTag);
}

/////////////////////////////////////////////////////////////
//For.Frame

//For.Getter
_bool Is_Call(const TCHAR* pFrameTag, const _float& fTimeDelta)
{
	return CFrameMgr::Get_Instance()->Is_Call(pFrameTag, fTimeDelta);
}

//For.Setter

//For.General
HRESULT Initialize_Frames(const TCHAR* pFrameTag, const _float& fLimitCall)
{
	return CFrameMgr::Get_Instance()->Initialize_Frames(pFrameTag, fLimitCall);
}

/////////////////////////////////////////////////////////////
//For.Release
void Engine::Release_System(void)
{
	CFontMgr::Get_Instance().~shared_ptr();
	CInput::Get_Instance().~shared_ptr();
	CGraphicDev::Get_Instance().~shared_ptr();
}
