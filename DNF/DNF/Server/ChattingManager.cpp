#include "stdafx.h"
#include "ChattingManager.h"
#include "../UI/DXUT.h"

IMPLEMENT_SINGLETON(ChattingManager)

HRESULT CALLBACK OnResetDevice(IDirect3DDevice9* pd3dDevice,
	const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	HRESULT hr;

	shared_ptr<ChattingManager> pChattingManger = ChattingManager::Get_Instance();

	V_RETURN(pChattingManger->Get_DialogResourceManager()->OnD3D9ResetDevice());

	pChattingManger->Get_ChattingUI()->SetLocation(0, 0);
	pChattingManger->Get_ChattingUI()->SetSize(pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height);

	pChattingManger->Get_ChattingUI()->GetControl(IDC_STATIC)->SetSize(pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height * 6 /
		10);
	pChattingManger->Get_ChattingUI()->GetControl(IDC_OUTPUT)->SetSize(pBackBufferSurfaceDesc->Width - 170, pBackBufferSurfaceDesc->Height /
		4);
	if (pChattingManger->Get_ChattingUI()->GetControl(IDC_EDITBOX2))
	{
		pChattingManger->Get_ChattingUI()->GetControl(IDC_EDITBOX2)->SetLocation(20, pBackBufferSurfaceDesc->Height - 280);
		pChattingManger->Get_ChattingUI()->GetControl(IDC_EDITBOX2)->SetSize(pBackBufferSurfaceDesc->Width - 40, 45);
	}
	pChattingManger->Get_ChattingUI()->GetControl(IDC_CLEAREDIT)->SetLocation(120, pBackBufferSurfaceDesc->Height - 25);


	return S_OK;
}

void CALLBACK OnLostDevice(void* pUserContext)
{
	ChattingManager::Get_Instance()->Get_DialogResourceManager()->OnD3D9LostDevice();	
}

void CALLBACK OnDestroyDevice(void* pUserContext)
{
	CDXUTIMEEditBox::Uninitialize();

	ChattingManager::Get_Instance()->Get_DialogResourceManager()->OnD3D9DestroyDevice();	
}

LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
	void* pUserContext)
{
	// Always allow dialog resource manager calls to handle global messages
	// so GUI state is updated correctly
	*pbNoFurtherProcessing = CDXUTIMEEditBox::StaticMsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;
	*pbNoFurtherProcessing = ChattingManager::Get_Instance()->Get_DialogResourceManager()->MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	// Give the dialogs a chance to handle the message first
	*pbNoFurtherProcessing = ChattingManager::Get_Instance()->Get_ChattingUI()->MsgProc(hWnd, uMsg, wParam, lParam);
	if (*pbNoFurtherProcessing)
		return 0;

	return 0;
}

void CALLBACK OnGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext)
{
	WCHAR wszOutput[1024];

	switch (nControlID)
	{
	case IDC_EDITBOX2:
		switch (nEvent)
		{
		case EVENT_EDITBOX_STRING:
		{
			swprintf_s(wszOutput, 1024,
				L"You have pressed Enter in edit control (ID %u).\nThe content of the edit control is:\n\"%s\"",
				nControlID, ((CDXUTEditBox*)pControl)->GetText());
			ChattingManager::Get_Instance()->Get_ChattingUI()->GetStatic(IDC_OUTPUT)->SetText(wszOutput);

			// Clear the text if needed
			if (ChattingManager::Get_Instance()->Get_ChattingUI()->GetCheckBox(IDC_CLEAREDIT)->GetChecked())
				((CDXUTEditBox*)pControl)->SetText(L"");
			break;
		}

		case EVENT_EDITBOX_CHANGE:
		{
			swprintf_s(wszOutput, 1024,
				L"You have changed the content of an edit control (ID %u).\nIt is now:\n\"%s\"",
				nControlID, ((CDXUTEditBox*)pControl)->GetText());
			ChattingManager::Get_Instance()->Get_ChattingUI()->GetStatic(IDC_OUTPUT)->SetText(wszOutput);

			break;
		}
		}
		break;
	}
}

ChattingManager::ChattingManager(void)
	: m_fTimeDelta(0.f)
{

}

void ChattingManager::Initialize_ChattingUI(void)
{
	m_ChattingUI.Init(&m_DialogResourceManager);
	m_ChattingUI.SetCallback(OnGUIEvent);
	m_ChattingUI.SetFont(1, L"Comic Sans MS", 24, FW_MEDIUM);		//폰트 셋팅
	m_ChattingUI.SetFont(2, L"Courier New", 20, FW_NORMAL);			//인덱스를 이용하여 폰트를 사용할 수 있다.

	// Static	
	//StaticControl의 위치와 크기를 설정해 줄 수 있다.
	m_ChattingUI.AddStatic(IDC_OUTPUT,
		L"채팅창입니다. 채팅을 출력해줍니다.",  (int)(WINSIZEX * 0.0375f), (int)(WINSIZEY * 0.075f), (int)(WINSIZEX * 0.625f), (int)(WINSIZEY * 0.5f));
	m_ChattingUI.GetStatic(IDC_OUTPUT)->SetTextColor(D3DCOLOR_ARGB(255, 0, 255, 0)); // Change color to red		//StaticControl 내부의 텍스트 색상 설정
	m_ChattingUI.GetControl(IDC_OUTPUT)->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;			//StaticControl 내부의 텍스트 정렬 설정
	m_ChattingUI.GetControl(IDC_OUTPUT)->GetElement(0)->iFont = 2;												//StaticControl	내부의 텍스트 폰트 설정
	//m_ChattingUI.GetStatic(IDC_STATIC)->SetTextColor(D3DCOLOR_ARGB(255, 0, 255, 0)); // Change color to green	
	//m_ChattingUI.GetControl(IDC_STATIC)->GetElement(0)->dwTextFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;

	// IME-enabled edit box
	CDXUTIMEEditBox* pIMEEdit;
	CDXUTIMEEditBox::InitDefaultElements(&m_ChattingUI);
	if (SUCCEEDED(CDXUTIMEEditBox::CreateIMEEditBox(&m_ChattingUI, IDC_EDITBOX2,
		L"Type and press Enter.", (int)(WINSIZEX * 0.0375f), (int)(WINSIZEY * 0.65f), (int)(WINSIZEX * 0.625f), (int)(WINSIZEY * 0.075f), false, &pIMEEdit)))
	{
		m_ChattingUI.AddControl(pIMEEdit);
		pIMEEdit->GetElement(0)->iFont = 2;
		pIMEEdit->GetElement(1)->iFont = 2;
		pIMEEdit->GetElement(9)->iFont = 2;
		pIMEEdit->GetElement(0)->TextureColor.Init(D3DCOLOR_ARGB(128, 0, 0, 0));  //창 내부의 투명도 및 색상 설정
		pIMEEdit->SetBorderWidth(5);													//테두리 두께 설정
		pIMEEdit->SetTextColor(D3DCOLOR_ARGB(255, 255, 255, 255));						//텍스트 색상 설정
		pIMEEdit->SetCaretColor(D3DCOLOR_ARGB(255, 255, 255, 255));						//깜빡이는 표시의 색상 설정
		pIMEEdit->SetSelectedTextColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		pIMEEdit->SetSelectedBackColor(D3DCOLOR_ARGB(255, 40, 72, 72));		
	}
}

HRESULT ChattingManager::Initialize_ChattingManager(void)
{
	// Set DXUT callbacks	
	//DXUTSetCallbackD3D9DeviceReset(OnResetDevice);	
	//DXUTSetCallbackD3D9DeviceLost(OnLostDevice);
	//DXUTSetCallbackD3D9DeviceDestroyed(OnDestroyDevice);
	//DXUTSetCallbackMsgProc(MsgProc);		
	//DXUTInit(true, true);

	CDXUTIMEEditBox::Initialize(g_hWnd);
	this->Initialize_ChattingUI();		
	m_DialogResourceManager.OnD3D9CreateDevice(Engine::Get_GraphicDev());	

	return S_OK;
}

void ChattingManager::Update(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;	
}

void ChattingManager::Render(void)
{	
	m_ChattingUI.OnRender(m_fTimeDelta);
}

ChattingManager::~ChattingManager(void)
{
	m_DialogResourceManager.OnD3D9DestroyDevice();
}