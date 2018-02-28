#pragma once

#include "GraphicDev.h"
#include "Input.h"
#include "FontMgr.h"
#include "TimeMgr.h"
#include "FrameMgr.h"

namespace Engine
{
	/////////////////////////////////////////////////////////////
	//For.GraphicDev

	//For.Getter
	inline LPDIRECT3DDEVICE9 Get_GraphicDev(void);

	//For.Setter

	//For.General
	inline HRESULT Initialize_GraphicDev(CGraphicDev::WINMODE Mode);	

	/////////////////////////////////////////////////////////////
	//For.Input

	//For.Getter
	inline _ubyte	Get_DIKeyState(_ubyte KeyFlag);
	inline _ubyte	Get_DIMouseState(CInput::MOUSEBTCLICK KeyFlag);
	inline _long	Get_DIMouseMove(CInput::MOUSEMOVE KeyFlag);
	inline _bool	Get_DIKeyIsDown(_ubyte KeyFlag);
	inline _bool	Get_DIKeyIsUp(_ubyte KeyFlag);
	inline _bool	Get_DIMouseDown(CInput::MOUSEBTCLICK KeyFlag);
	inline _bool	Get_DIMouseUp(CInput::MOUSEBTCLICK KeyFlag);

	//For.Setter
	inline void Set_InputState(void);

	//For.General
	inline HRESULT Initialize_InputDevice();

	/////////////////////////////////////////////////////////////
	//For.Font

	//For.Getter

	//For.Setter

	//For.General
	inline HRESULT	Add_Font(const TCHAR* pFontKey, const _uint& iHeight, const _uint& iWidth, const _uint& iWeight);
	inline void		Render_Font(const TCHAR* pFontKey, const _vec3& vPos, const TCHAR* pString, _color Color);

	/////////////////////////////////////////////////////////////
	//For.Timer

	//For.Getter
	inline _float	Get_TimeDelta(const TCHAR* pTimerTag);

	//For.Setter
	inline void		Set_TimeDelta(const TCHAR* pTimerTag);

	//For.General
	inline HRESULT	Initialize_Timers(const TCHAR* pTimerTag);

	/////////////////////////////////////////////////////////////
	//For.Frame

	//For.Getter
	inline _bool Is_Call(const TCHAR* pFrameTag, const _float& fTimeDelta);

	//For.Setter

	//For.General
	inline HRESULT Initialize_Frames(const TCHAR* pFrameTag, const _float& fLimitCall);

	/////////////////////////////////////////////////////////////
	//For.Release
	inline void Release_System(void);

#include "Export_System.inl"

}