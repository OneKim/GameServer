#include "stdafx.h"
#include "ChattingManager.h"
#include "../UI/DXUT.h"

IMPLEMENT_SINGLETON(ChattingManager)

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
			/*swprintf_s(wszOutput, 1024,
				L"You have pressed Enter in edit control (ID %u).\nThe content of the edit control is:\n\"%s\"",
				nControlID, ((CDXUTEditBox*)pControl)->GetText());
			ChattingManager::Get_Instance()->Get_ChattingUI()->GetStatic(IDC_OUTPUT)->SetText(wszOutput);
			((CDXUTEditBox*)pControl)->SetText(L"");*/

			swprintf_s(wszOutput, 1024, L"%s : %s",
				Engine::Get_ID().c_str(), ((CDXUTEditBox*)pControl)->GetText());
			ChattingManager::Get_Instance()->Get_ChattingUI()->GetStatic(IDC_OUTPUT)->SetText(wszOutput);
			((CDXUTEditBox*)pControl)->SetText(L"");
			break;
		}

		/*case EVENT_EDITBOX_CHANGE:
		{
			swprintf_s(wszOutput, 1024,
				L"You have changed the content of an edit control (ID %u).\nIt is now:\n\"%s\"",
				nControlID, ((CDXUTEditBox*)pControl)->GetText());
			ChattingManager::Get_Instance()->Get_ChattingUI()->GetStatic(IDC_OUTPUT)->SetText(wszOutput);

			break;
		}*/
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
	m_ChattingUI.SetFont(1, L"Comic Sans MS", 24, FW_MEDIUM);		//��Ʈ ����
	m_ChattingUI.SetFont(2, L"Courier New", 20, FW_NORMAL);			//�ε����� �̿��Ͽ� ��Ʈ�� ����� �� �ִ�.

	// Static	
	//StaticControl�� ��ġ�� ũ�⸦ ������ �� �� �ִ�.
	m_ChattingUI.AddStatic(IDC_OUTPUT,
		L"ä��â�Դϴ�. ä���� ������ݴϴ�.",  (int)(WINSIZEX * 0.0375f), (int)(WINSIZEY * 0.075f), (int)(WINSIZEX * 0.625f), (int)(WINSIZEY * 0.5f));
	m_ChattingUI.GetStatic(IDC_OUTPUT)->SetTextColor(D3DCOLOR_ARGB(255, 0, 255, 0)); // Change color to red		//StaticControl ������ �ؽ�Ʈ ���� ����
	m_ChattingUI.GetControl(IDC_OUTPUT)->GetElement(0)->dwTextFormat = DT_LEFT | DT_TOP | DT_WORDBREAK;			//StaticControl ������ �ؽ�Ʈ ���� ����
	m_ChattingUI.GetControl(IDC_OUTPUT)->GetElement(0)->iFont = 2;												//StaticControl	������ �ؽ�Ʈ ��Ʈ ����
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
		pIMEEdit->GetElement(0)->TextureColor.Init(D3DCOLOR_ARGB(128, 0, 0, 0));		//â ������ ���� �� ���� ����
		pIMEEdit->SetBorderWidth(5);													//�׵θ� �β� ����
		pIMEEdit->SetTextColor(D3DCOLOR_ARGB(255, 255, 255, 255));						//�ؽ�Ʈ ���� ����
		pIMEEdit->SetCaretColor(D3DCOLOR_ARGB(255, 255, 255, 255));						//�����̴� ǥ���� ���� ����
		pIMEEdit->SetSelectedTextColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		pIMEEdit->SetSelectedBackColor(D3DCOLOR_ARGB(255, 40, 72, 72));		
	}
}

HRESULT ChattingManager::Initialize_ChattingManager(void)
{
	m_DialogResourceManager.OnD3D9CreateDevice(Engine::Get_GraphicDev());
	CDXUTIMEEditBox::Initialize(g_hWnd);
	this->Initialize_ChattingUI();

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

void ChattingManager::Set_MsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	CDXUTIMEEditBox::StaticMsgProc(g_hWnd, message, wParam, lParam);

	m_ChattingUI.MsgProc(g_hWnd, message, wParam, lParam);
}

ChattingManager::~ChattingManager(void)
{
	CDXUTIMEEditBox::Uninitialize();
	m_DialogResourceManager.OnD3D9DestroyDevice();
}