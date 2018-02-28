#include "stdafx.h"
#include "GraphicDev.h"

IMPLEMENT_SINGLETON(CGraphicDev)

CGraphicDev::CGraphicDev(void)
	: m_pSDK(NULL)
	, m_pDevice(NULL)
{
}

void CGraphicDev::Set_Parameters(D3DPRESENT_PARAMETERS & d3dpp, WINMODE Mode)
{
	d3dpp.BackBufferWidth = WINSIZEX;
	d3dpp.BackBufferHeight = WINSIZEY;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleQuality = 0;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = TRUE;

	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = Mode;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

HRESULT CGraphicDev::Initialize_GraphicDev(WINMODE Mode)
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		devicecaps;
	ZeroMemory(&devicecaps, sizeof(D3DCAPS9));

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devicecaps)))
	{
		MSG_BOX(L"GetDeviceCaps Failed");
		return E_FAIL;
	}

	_ulong	vp;

	if (devicecaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	vp |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	Set_Parameters(d3dpp, Mode);

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL
		, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		MSG_BOX(L"CreateDevice Failed");
		return E_FAIL;
	}

	return S_OK;
}

CGraphicDev::~CGraphicDev(void)
{
	_int iCnt = m_pDevice->Release();
	if (iCnt)
		MSG_BOX(L"GraphicDev Release Failed");

	iCnt = m_pSDK->Release();
	if (iCnt)
		MSG_BOX(L"SDK Release Failed");
}