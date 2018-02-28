#pragma once

class CInput
{
public:
	DECLARE_SINGLETON(CInput)
public:
	enum MOUSEBTCLICK { DIM_LBUTTON, DIM_RBUTTON, DIM_MBUTTON };
	enum MOUSEMOVE { DIM_X, DIM_Y, DIM_Z };
private:
	LPDIRECTINPUT8			m_pInput;
	LPDIRECTINPUTDEVICE8	m_pKeyBoard;
	LPDIRECTINPUTDEVICE8	m_pMouse;
private:
	_ubyte			m_byPrevKeyState[256]	= {};
	_ubyte			m_byKeyState[256]		= {};
	DIMOUSESTATE	m_PrevMouseState		= {};
	DIMOUSESTATE	m_MouseState			= {};
private:
	explicit CInput(void);
private:
	HRESULT Initialize_KeyBoard(void);
	HRESULT Initialize_Mouse(void);
public:
	HRESULT	Initialize_InputDevice(void);
	void	Set_InputState(void);
public:
	_ubyte	Get_DIKeyState(_ubyte KeyFlag);
	_ubyte	Get_DIMouseState(MOUSEBTCLICK KeyFlag);
	_long	Get_DIMouseMove(MOUSEMOVE KeyFlag);

	_bool	Get_KeyDown(BYTE KeyFlag);
	_bool	Get_KeyUp(BYTE KeyFlag);
	_bool	Get_MouseDown(MOUSEBTCLICK KeyFlag);
	_bool	Get_MouseUp(MOUSEBTCLICK KeyFlag);
public:
	~CInput(void);
};