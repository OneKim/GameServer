#include "stdafx.h"
#include "GameManager.h"
#include "Scene.h"

IMPLEMENT_SINGLETON(CGameManager)

CGameManager::CGameManager(void)
	: m_pScene(NULL)
	, m_pRenderer(NULL)
{

}

HRESULT CGameManager::Initialize_GameManager(void)
{
	m_pRenderer = auto_ptr<CRenderer>(CRenderer::Create());
	NULL_CHECK_RETURN(m_pRenderer.get(), E_FAIL);

	return S_OK;
}

void CGameManager::Update(const _float & fTimeDelta)
{
	NULL_CHECK(m_pScene);
	m_pScene->Update(fTimeDelta);
}

void CGameManager::Render(void)
{
	NULL_CHECK(m_pRenderer.get());
	m_pRenderer->Render();
}

CGameManager::OBJECTLIST * CGameManager::Get_ObjList(const TCHAR * pLayerKey, const TCHAR * pObjectKey)
{
	NULL_CHECK_RETURN(m_pScene, NULL);
	return m_pScene->Get_ObjList(pLayerKey, pObjectKey);
}

CGameObject* CGameManager::Get_Object(const TCHAR * pLayerKey, const TCHAR * pObjectKey, _ulong dwIndex)
{
	NULL_CHECK_RETURN(m_pScene, NULL);
	return m_pScene->Get_Object(pLayerKey, pObjectKey, dwIndex);
}

CComponent* CGameManager::Get_Component(const TCHAR * pLayerKey, const TCHAR * pObjectKey, const TCHAR * pComKey, _ulong dwIndex)
{
	NULL_CHECK_RETURN(m_pScene, NULL);
	return m_pScene->Get_Component(pLayerKey, pObjectKey, pComKey, dwIndex);
}

HRESULT CGameManager::Add_Object(const TCHAR * pLayerKey, const TCHAR * pObjectKey, CGameObject * pGameObject)
{
	NULL_CHECK_RETURN(m_pScene, E_FAIL);
	return m_pScene->Add_Object(pLayerKey, pObjectKey, pGameObject);
}

void CGameManager::Add_RenderGroup(CRenderer::RENDERGROUP eGroup, CGameObject* pGameObject)
{
	NULL_CHECK(m_pRenderer.get());

	m_pRenderer->Add_RenderGroup(eGroup, pGameObject);
}

void CGameManager::Set_SceneChange(CLoading::LOADINGTYPE eLoadingScene)
{
	NULL_CHECK(m_pScene);
	
	m_pScene->Set_SceneChange(eLoadingScene);
}

CGameManager::~CGameManager(void)
{
	Safe_Delete(m_pScene);
}
