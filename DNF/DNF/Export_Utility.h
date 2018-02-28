#pragma once

#include "GameManager.h"

namespace Engine
{
	typedef list<CGameObject*>				OBJECTLIST;
	/////////////////////////////////////////////////////////////
	//For.GameManager

	// For.Getter
	inline OBJECTLIST*				Get_ObjectList(const TCHAR* pLayerKey, const TCHAR* pObjectKey);
	inline CGameObject*	Get_Object(const TCHAR* pLayerKey, const TCHAR* pObjectKey, const _ulong& dwIndex = 0);
	inline CComponent*	Get_Component(const TCHAR* pLayerKey, const TCHAR* pObjectKey, const TCHAR* pComKey, _ulong dwIndex = 0);	

	// For.Setter
	inline void		Set_SceneChange(CLoading::LOADINGTYPE eLoadingScene);

	// For.General
	inline HRESULT	Add_Object(const TCHAR* pLayerKey, const TCHAR* pObjectKey, CGameObject* pGameObject);
	inline void		Add_RenderGroup(CRenderer::RENDERGROUP eGroup, CGameObject* pGameObject);
	inline HRESULT	Initialize_GameManager(void);
	inline void		Update_GameManager(const _float& fTimeDelta);
	inline void		Render_GameManager(void);
	template <typename T> HRESULT Change_Scene(T& Functor);

	/////////////////////////////////////////////////////////////
	//For.Release
	inline void Release_Utility(void);

#include "Export_Utility.inl"

}