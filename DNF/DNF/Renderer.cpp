#include "stdafx.h"
#include "Renderer.h"
#include "GameObject.h"

_bool Compare(CGameObject* pDest, CGameObject* pSour)
{
	return pDest->Get_ViewZ() > pSour->Get_ViewZ();
}

CRenderer::CRenderer(void)
	: m_pScene(NULL)
	, m_pGraphicDev(NULL)
{
}

void CRenderer::Render_Priority(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);

	RENDERLIST::iterator	iter = m_RenderGroup[TYPE_PRIORITY].begin();
	RENDERLIST::iterator	iter_end = m_RenderGroup[TYPE_PRIORITY].end();

	for (; iter != iter_end; ++iter)
	{
		(*iter)->Render();
	}

	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void CRenderer::Render_NoneAlpha(void)
{
	RENDERLIST::iterator	iter = m_RenderGroup[TYPE_NONEALPHA].begin();
	RENDERLIST::iterator	iter_end = m_RenderGroup[TYPE_NONEALPHA].end();

	for (; iter != iter_end; ++iter)
	{
		(*iter)->Render();
	}
}

void CRenderer::Render_Alpha(void)
{
	m_RenderGroup[TYPE_ALPHA].sort(Compare);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	RENDERLIST::iterator	iter = m_RenderGroup[TYPE_ALPHA].begin();
	RENDERLIST::iterator	iter_end = m_RenderGroup[TYPE_ALPHA].end();

	for (; iter != iter_end; ++iter)
	{
		(*iter)->Render();
	}

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CRenderer::Render_UI(void)
{
	m_RenderGroup[TYPE_UI].sort(Compare);

	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);

	RENDERLIST::iterator	iter = m_RenderGroup[TYPE_UI].begin();
	RENDERLIST::iterator	iter_end = m_RenderGroup[TYPE_UI].end();

	for (; iter != iter_end; ++iter)
	{
		(*iter)->Render();
	}

	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void CRenderer::Clear_RenderGroup(void)
{
	for (_ulong i = 0; i < TYPE_END; ++i)
	{
		m_RenderGroup[i].clear();
	}
}

HRESULT CRenderer::Initialize_Renderer(void)
{
	m_pGraphicDev = Engine::Get_GraphicDev();

	return S_OK;
}

void CRenderer::Render(void)
{
	Render_Priority();
	Render_NoneAlpha();
	Render_Alpha();
	Render_UI();
	Clear_RenderGroup();
}

void CRenderer::SetCurrentScene(CScene* pScene)
{
	m_pScene = pScene;
}

void CRenderer::Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pGameObject)
{
	if (NULL == pGameObject)
		return;	

	m_RenderGroup[eGroup].push_back(pGameObject);
}

CRenderer * CRenderer::Create(void)
{
	CRenderer* pRenderer = new CRenderer();
	if (FAILED(pRenderer->Initialize_Renderer()))
	{
		Safe_Delete(pRenderer);
	}
	return pRenderer;
}

CRenderer::~CRenderer(void)
{
	Clear_RenderGroup();
}
