#pragma once

#include "Loading.h"
#include "Layer.h"

class CComponent;
class CGameObject;
class CScene abstract
{
protected:
	typedef list<CGameObject*>							OBJECTLIST;
	typedef map<const TCHAR*, CLayer*>					MAPLAYER;
protected:
	MAPLAYER				m_mapLayer;	
	CLoading::LOADINGTYPE	m_eLoadingScene;
	_bool					m_bSceneChange;
protected:
	explicit	CScene(void);
protected:
	virtual HRESULT Initialize_Resource(void) PURE;
	virtual HRESULT Initialize_Layer_Environment(void) PURE;
	virtual HRESULT Initialize_Layer_GameLogic(void) PURE;
	virtual HRESULT Initialize_Layer_UI(void) PURE;
public:
	virtual HRESULT Initialize_Scene(void) PURE;
	virtual void	Update(const _float& fTimeDelta);
	virtual void	Render(void);
public:
	OBJECTLIST*				Get_ObjList(const TCHAR* pLayerKey, const TCHAR* pObjectKey);	
	CGameObject* Get_Object(const TCHAR* pLayerKey, const TCHAR* pObjectKey, _ulong dwIndex);
	CComponent*				Get_Component(const TCHAR* pLayerKey, const TCHAR* pObjectKey, const TCHAR* pComKey, _ulong dwIndex);
	HRESULT					Add_Object(const TCHAR* pLayerKey, const TCHAR* pObjectKey, CGameObject* pGameObject);
public:
	void		Set_SceneChange(CLoading::LOADINGTYPE eLoadingScene);
	_bool		Is_SceneChange(void);
public:
	virtual ~CScene(void);
};