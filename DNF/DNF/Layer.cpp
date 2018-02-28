#include "stdafx.h"
#include "Layer.h"
#include "GameObject.h"

CLayer::CLayer(void)
{
}

void CLayer::Update(const _float & fTimeDelta)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.begin();
	MAPOBJLIST::iterator	iter_end = m_mapObjlist.end();

	for (; iter != iter_end; ++iter)
	{
		OBJECTLIST::iterator	iterList = iter->second.begin();
		OBJECTLIST::iterator	iterList_end = iter->second.end();
		
		for (; iterList != iterList_end; ++iterList)
			(*iterList)->Update(fTimeDelta);
	}
}

void CLayer::Render(void)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.begin();
	MAPOBJLIST::iterator	iter_end = m_mapObjlist.end();

	for (; iter != iter_end; ++iter)
	{
		OBJECTLIST::iterator	iterList = iter->second.begin();
		OBJECTLIST::iterator	iterList_end = iter->second.end();

		for (; iterList != iterList_end; ++iterList)
			(*iterList)->Render();
	}
}

CLayer::OBJECTLIST * CLayer::Get_ObjList(const TCHAR * pObjectKey)
{
	MAPOBJLIST::iterator iter = find_if(m_mapObjlist.begin(), m_mapObjlist.end(), CTagFinder(pObjectKey));
	if (iter == m_mapObjlist.end())
		return NULL;

	return &(iter->second);
}

CGameObject* CLayer::Get_Object(const TCHAR * pObjectKey, _ulong dwIndex)
{
	OBJECTLIST* pObjList = Get_ObjList(pObjectKey);
	if (NULL == pObjList)
		return NULL;

	OBJECTLIST::iterator iterList = pObjList->begin();
	OBJECTLIST::iterator iterList_End = pObjList->end();
	for (_ulong i = 0; i < dwIndex && iterList != iterList_End; ++iterList, ++i)

	if (iterList == iterList_End)
		return NULL;

	return *iterList;
}

CComponent* CLayer::Get_Component(const TCHAR * pObjectKey, const TCHAR * pComKey, _ulong dwIndex)
{
	OBJECTLIST* pObjList = Get_ObjList(pObjectKey);
	if (NULL == pObjList)
		return NULL;

	OBJECTLIST::iterator iterList		= pObjList->begin();
	OBJECTLIST::iterator iterList_End	= pObjList->end();
	for(_ulong i = 0; i < dwIndex && iterList != iterList_End; ++i, ++iterList)

	if(iterList == iterList_End)
		return NULL;

	return (*iterList)->Get_Component(pComKey);
}

HRESULT CLayer::Add_Object(const TCHAR * pObjectKey, CGameObject * pGameObject)
{
	if (pGameObject)
	{
		MAPOBJLIST::iterator	iter = find_if(m_mapObjlist.begin(), m_mapObjlist.end(), CTagFinder(pObjectKey));
		if(iter == m_mapObjlist.end())
			m_mapObjlist[pObjectKey] = OBJECTLIST();
		m_mapObjlist[pObjectKey].push_back(pGameObject);
	}

	return S_OK;
}

CLayer * CLayer::Create(void)
{
	return new CLayer();
}

CLayer::~CLayer(void)
{
	for (auto objectlist : m_mapObjlist)
	{
		for (auto object : objectlist.second)
			Safe_Delete(object);
		objectlist.second.clear();
	}
}
