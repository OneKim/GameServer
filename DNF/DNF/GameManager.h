#pragma once

#include "Loading.h"
#include "Renderer.h"

class CScene;
class CGameObject;
class CComponent;

class CGameManager
{
	DECLARE_SINGLETON(CGameManager)
private:
	typedef list<CGameObject*>	OBJECTLIST;
private:
	CScene*					m_pScene;
	shared_ptr<CRenderer>		m_pRenderer;
private:
	explicit	CGameManager(void);
public:
	HRESULT Initialize_GameManager(void);
	void Update(const _float& fTimeDelta);
	void Render(void);
public:
	OBJECTLIST*				Get_ObjList(const TCHAR* pLayerKey, const TCHAR* pObjectKey);
	CGameObject*	Get_Object(const TCHAR* pLayerKey, const TCHAR* pObjectKey, _ulong dwIndex);
	CComponent*	Get_Component(const TCHAR* pLayerKey, const TCHAR* pObjectKey, const TCHAR* pComKey, _ulong dwIndex);
	HRESULT	Add_Object(const TCHAR* pLayerKey, const TCHAR* pObjectKey, CGameObject* pGameObject);
	void	Add_RenderGroup(CRenderer::RENDERGROUP eGroup, CGameObject* pGameObject);
public:
	template <typename T>
	HRESULT Change_Scene(T& Functor);
	void	Set_SceneChange(CLoading::LOADINGTYPE eLoadingScene);
public:
	~CGameManager(void);
};

template<typename T>
inline HRESULT CGameManager::Change_Scene(T & Functor)
{
	if (m_pScene != NULL)
		Safe_Delete(m_pScene);

	FAILED_CHECK_RETURN(Functor(&m_pScene), E_FAIL);

	m_pRenderer->SetCurrentScene(m_pScene);

	return S_OK;
}
