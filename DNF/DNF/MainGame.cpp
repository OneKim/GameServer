#include "stdafx.h"
#include "MainGame.h"
#include "SceneSelector.h"
#include "Texture.h"

_matrix g_matOrtho;

CMainGame::CMainGame(void)
	: m_pGraphicDev(NULL)
	, m_fAccTime(0.f)
	, m_usNumRender(0)
{

}

HRESULT CMainGame::Initialize_MainGame(void)
{
	FAILED_CHECK_MSG(Engine::Initialize_GraphicDev(CGraphicDev::WINMODE::MODE_WIN), L"Initialize_GraphicDev Failed!");	
	m_pGraphicDev = Engine::Get_GraphicDev();
	D3DXMatrixOrthoLH(&g_matOrtho, (_float)WINSIZEX, (_float)WINSIZEY, 0.0f, 1.f);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &g_matOrtho);

	FAILED_CHECK_MSG(Engine::Initialize_InputDevice(), L"Initialize_InputDevice Failed!");

	FAILED_CHECK_MSG(Engine::Add_Font(L"¹ÙÅÁ", 20, 14, FW_HEAVY), L"Add_Font Failed!");
	FAILED_CHECK_MSG(Engine::Add_Font(L"HYÅÂ¹éB", 20, 14, FW_HEAVY), L"Add_Font Failed!");
	FAILED_CHECK_MSG(Engine::Add_Font(L"¸¼Àº °íµñ", 14, 9, FW_BOLD), L"Add_Font Failed!");

	FAILED_CHECK_MSG(Engine::Initialize_Timers(L"TimeDelta:Immediate"), L"Initialize_Timers Failed!");
	FAILED_CHECK_MSG(Engine::Initialize_Timers(L"TimeDelta:60"), L"Initialize_Timers Failed!");

	FAILED_CHECK_MSG(Engine::Initialize_Frames(L"Frame:60", 60.f), L"Initialize_Frames Failed!");

	FAILED_CHECK_MSG(Engine::Initialize_GameManager(), L"Initialize_GameManager Failed!");

	//FAILED_CHECK_MSG(Engine::Initialize_ServerManager(), L"Initialize_ServerManager Failed!");

	FAILED_CHECK_MSG(Engine::Initialize_ChattingManager(), L"Initialize_ChattingManager Failed!");

	FAILED_CHECK_MSG(Initialize_Resource(), L"Initialize_Resource Failed!");

	FAILED_CHECK_MSG(Engine::Change_Scene(CSceneSelector(SCENE_SR, CLoading::LOADING_SR)), L"Change_Scene Failed!");

	return S_OK;
}

HRESULT CMainGame::Initialize_Resource(void)
{
	Engine::Reserve_ContainerSize(RESOURCE_END);

	FAILED_CHECK(Engine::Add_Buffer(RESOURCE_STATIC, CVIBuffer::BUFFER_RCTEX, L"Buffer_RcTex"));//

	FAILED_CHECK(Engine::Add_Texture(RESOURCE_STATIC, L"Texture_SeriaRoom", L"../Resources/Textures/SeriaRoom/SeriaRoom.png"));
	FAILED_CHECK(Engine::Add_Texture(RESOURCE_STATIC, L"Texture_Player", L"../Resources/Textures/Player/Player.png"));

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void CMainGame::Update(const _float& fTimeDelta)
{
	m_fAccTime += fTimeDelta;

	Engine::Set_InputState();

	Engine::Update_GameManager(fTimeDelta);

	//Engine::Update_ServerManager(fTimeDelta);

	Engine::Update_ChattingManager(fTimeDelta);
}

void CMainGame::Render(void)
{
	++m_usNumRender;

	if (m_fAccTime >= 1.f)
	{
		wsprintf(m_szFPS, L"FPS:%d", m_usNumRender);
		m_usNumRender = 0;
		m_fAccTime = 0.f;
	}

	m_pGraphicDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);

	m_pGraphicDev->BeginScene();

	Engine::Render_GameManager();

	Engine::Render_ChattingManager();

	Engine::Render_Font(L"¸¼Àº °íµñ", _vec3(WINSIZEX * 0.91f, 0.f, 0.f), m_szFPS, _color(0.f, 1.f, 0.f, 1.f));

	m_pGraphicDev->EndScene();

	m_pGraphicDev->Present(NULL, NULL, NULL, NULL);

}

CMainGame* CMainGame::Create(void)
{
	CMainGame* pInstance = new CMainGame;

	if (FAILED(pInstance->Initialize_MainGame()))
	{
		MSG_BOX(L"CMainApp Created Failed");
		Safe_Delete(pInstance);
	}

	return pInstance;
}

CMainGame::~CMainGame(void)
{
	Engine::Release_Utility();
	Engine::Release_Resources();
	//Engine::Release_Server();
	Engine::Release_System();
}