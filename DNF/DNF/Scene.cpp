#include "stdafx.h"
#include "Scene.h"
#include "GameManager.h"
#include "SceneSelector.h"

CScene::CScene(void)
	: m_eLoadingScene(CLoading::LOADING_END)
	, m_bSceneChange(false)
{
}

void CScene::Update(const _float & fTimeDelta)
{
	MAPLAYER::iterator	iter = m_mapLayer.begin();
	MAPLAYER::iterator	iter_end = m_mapLayer.end();

	for (; iter != iter_end; ++iter)
		iter->second->Update(fTimeDelta);
}

void CScene::Render(void)
{
	MAPLAYER::iterator	iter = m_mapLayer.begin();
	MAPLAYER::iterator	iter_end = m_mapLayer.end();

	for (; iter != iter_end; ++iter)
		iter->second->Render();
}

CScene::OBJECTLIST * CScene::Get_ObjList(const TCHAR * pLayerKey, const TCHAR * pObjectKey)
{
	MAPLAYER::iterator iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTagFinder(pLayerKey));
	if (iter == m_mapLayer.end())
		return NULL;

	return iter->second->Get_ObjList(pObjectKey);
}

CGameObject* CScene::Get_Object(const TCHAR * pLayerKey, const TCHAR * pObjectKey, _ulong dwIndex)
{
	MAPLAYER::iterator iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTagFinder(pLayerKey));
	if (iter == m_mapLayer.end())
		return NULL;

	return iter->second->Get_Object(pObjectKey, dwIndex);
}

CComponent* CScene::Get_Component(const TCHAR * pLayerKey, const TCHAR * pObjectKey, const TCHAR * pComKey, _ulong dwIndex)
{
	MAPLAYER::iterator iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTagFinder(pLayerKey));
	if (iter == m_mapLayer.end())
		return NULL;

	return iter->second->Get_Component(pObjectKey, pComKey, dwIndex);
}

HRESULT CScene::Add_Object(const TCHAR * pLayerKey, const TCHAR * pObjectKey, CGameObject * pGameObject)
{
	MAPLAYER::iterator iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTagFinder(pLayerKey));
	if (iter == m_mapLayer.end())
		return NULL;

	return iter->second->Add_Object(pObjectKey, pGameObject);
}

void CScene::Set_SceneChange(CLoading::LOADINGTYPE eLoadingScene)
{
	m_eLoadingScene = eLoadingScene;
	m_bSceneChange = true;	
}

_bool CScene::Is_SceneChange(void)
{
	if (true == m_bSceneChange)
	{
		if (SUCCEEDED(CGameManager::Get_Instance()->Change_Scene(CSceneSelector(SCENE_NS, m_eLoadingScene))))
			return true;
	}
	return false;
}

CScene::~CScene(void)
{
	for (auto layer : m_mapLayer)
		Safe_Delete(layer.second);

	m_mapLayer.clear();
}
