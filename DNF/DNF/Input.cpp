#include "stdafx.h"
#include "Input.h"

IMPLEMENT_SINGLETON(CInput)

CInput::CInput(void)
	: m_pInput(NULL)
	, m_pKeyBoard(NULL)
	, m_pMouse(NULL)
{
}

HRESULT CInput::Initialize_KeyBoard(void)
{
	FAILED_CHECK(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, NULL));

	FAILED_CHECK(m_pKeyBoard->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE/* | DISCL_NOWINKEY*/));

	FAILED_CHECK(m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard));

	m_pKeyBoard->Acquire();

	return S_OK;
}

HRESULT CInput::Initialize_Mouse(void)
{
	FAILED_CHECK(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL));

	FAILED_CHECK(m_pMouse->SetCooperativeLevel(g_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE/* | DISCL_NOWINKEY*/));

	FAILED_CHECK(m_pMouse->SetDataFormat(&c_dfDIMouse));

	m_pMouse->Acquire();

	return S_OK;
}

HRESULT CInput::Initialize_InputDevice()
{
	FAILED_CHECK_MSG(DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL), L"DirectInput Initialize Failed");

	FAILED_CHECK_MSG(Initialize_KeyBoard(), L"KeyBoard Initialize Failed");

	FAILED_CHECK_MSG(Initialize_Mouse(), L"Mouse Initialize Failed");

	return S_OK;
}

void CInput::Set_InputState(void)
{
	memcpy(m_byPrevKeyState, m_byKeyState, sizeof(BYTE) * 256);
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);

	memcpy(&m_PrevMouseState, &m_MouseState, sizeof(DIMOUSESTATE));
	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState);
}

_ubyte CInput::Get_DIKeyState(_ubyte KeyFlag)
{
	return m_byKeyState[KeyFlag];
}

_ubyte CInput::Get_DIMouseState(MOUSEBTCLICK KeyFlag)
{
	return m_MouseState.rgbButtons[KeyFlag];
}

_long CInput::Get_DIMouseMove(MOUSEMOVE KeyFlag)
{
	switch (KeyFlag) {
	case CInput::DIM_X: return m_MouseState.lX;
	case CInput::DIM_Y:	return m_MouseState.lY;
	case CInput::DIM_Z:	return m_MouseState.lZ;
	}
	return 0;
}

_bool CInput::Get_KeyDown(BYTE KeyFlag)
{
	return ((m_byKeyState[KeyFlag] & 0x80) && !(m_byPrevKeyState[KeyFlag] & 0x80)) ? true : false;
}

_bool CInput::Get_KeyUp(BYTE KeyFlag)
{
	return (!(m_byKeyState[KeyFlag] & 0x80) && (m_byPrevKeyState[KeyFlag] & 0x80)) ? true : false;
}

_bool CInput::Get_MouseDown(MOUSEBTCLICK KeyFlag)
{
	return ((m_MouseState.rgbButtons[KeyFlag] & 0x80) && !(m_PrevMouseState.rgbButtons[KeyFlag] & 0x80));
}

_bool CInput::Get_MouseUp(MOUSEBTCLICK KeyFlag)
{
	return (!(m_MouseState.rgbButtons[KeyFlag] & 0x80) && (m_PrevMouseState.rgbButtons[KeyFlag] & 0x80));
}

CInput::~CInput(void)
{
	Safe_Release(m_pMouse);
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pInput);
}
