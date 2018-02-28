/////////////////////////////////////////////////////////////
//For.GameManager

// For.Getter
Engine::OBJECTLIST * Engine::Get_ObjectList(const TCHAR * pLayerKey, const TCHAR * pObjectKey)
{
	return CGameManager::Get_Instance()->Get_ObjList(pLayerKey, pObjectKey);
}

CGameObject* Engine::Get_Object(const TCHAR * pLayerKey, const TCHAR * pObjectKey, const _ulong & dwIndex)
{
	return CGameManager::Get_Instance()->Get_Object(pLayerKey, pObjectKey, dwIndex);
}

CComponent* Engine::Get_Component(const TCHAR * pLayerKey, const TCHAR * pObjectKey, const TCHAR * pComKey, _ulong dwIndex)
{
	return CGameManager::Get_Instance()->Get_Component(pLayerKey, pObjectKey, pComKey, dwIndex);
}

// For.Setter
void Engine::Set_SceneChange(CLoading::LOADINGTYPE eLoadingScene)
{
	CGameManager::Get_Instance()->Set_SceneChange(eLoadingScene);
}

// For.General
HRESULT Engine::Add_Object(const TCHAR * pLayerKey, const TCHAR * pObjectKey, CGameObject * pGameObject)
{
	return CGameManager::Get_Instance()->Add_Object(pLayerKey, pObjectKey, pGameObject);
}

void Engine::Add_RenderGroup(CRenderer::RENDERGROUP eGroup, CGameObject* pGameObject)
{
	CGameManager::Get_Instance()->Add_RenderGroup(eGroup, pGameObject);
}

HRESULT Engine::Initialize_GameManager(void)
{
	return CGameManager::Get_Instance()->Initialize_GameManager();
}

void Engine::Update_GameManager(const _float & fTimeDelta)
{
	CGameManager::Get_Instance()->Update(fTimeDelta);
}

void Engine::Render_GameManager(void)
{
	CGameManager::Get_Instance()->Render();
}

template <typename T> HRESULT Engine::Change_Scene(T& Functor)
{
	return CGameManager::Get_Instance()->Change_Scene(Functor);
}

/////////////////////////////////////////////////////////////
//For.Release
void Engine::Release_Utility(void)
{
	CGameManager::Get_Instance().~shared_ptr();
}