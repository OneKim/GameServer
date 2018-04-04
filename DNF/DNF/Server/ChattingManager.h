#pragma once

#include "../UI/DXUTgui.h"

#define IDC_EDITBOX2            6
#define IDC_STATIC              10
#define IDC_OUTPUT              12

class ChattingManager
{
	DECLARE_SINGLETON(ChattingManager)
private:
	CDXUTDialog					m_ChattingUI;		
	CDXUTDialogResourceManager  m_DialogResourceManager;
	_float						m_fTimeDelta;
private:
	explicit					ChattingManager(void);
	void						Initialize_ChattingUI(void);
public:
	HRESULT						Initialize_ChattingManager(void);
	void						Update(const _float& fTimeDelta);
	void						Render(void);
	CDXUTDialog*				Get_ChattingUI(void) {	return &m_ChattingUI; }
	CDXUTDialogResourceManager* Get_DialogResourceManager(void) { return &m_DialogResourceManager; }
	void						Set_MsgProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	~ChattingManager(void);
};