#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

CGameObject::CGameObject()
	: m_fViewZ(0.f)
	, m_fTimeDelta(0.f)
{
}

HRESULT CGameObject::AddComponent(void)
{
	return S_OK;
}

void CGameObject::Compute_ViewZ(const _vec3* pPosition)
{
}

HRESULT CGameObject::Initialize_GameObject(void)
{
	return E_NOTIMPL;
}

void CGameObject::Update(const _float & fTimeDelta)
{
	MAPCOMPONENT::iterator	iter = m_mapComponent.begin();
	MAPCOMPONENT::iterator	iter_end = m_mapComponent.end();
	for (; iter != iter_end; ++iter)
		iter->second->Update();
}

void CGameObject::Render(void)
{
}

CComponent* CGameObject::Get_Component(const TCHAR * pComKey)
{
	MAPCOMPONENT::iterator iter = find_if(m_mapComponent.begin(), m_mapComponent.end(), CTagFinder(pComKey));
	if(iter == m_mapComponent.end())
		return NULL;

	return iter->second;
}

const _float & CGameObject::Get_ViewZ(void)
{
	return m_fViewZ;
}

CGameObject::~CGameObject(void)
{
	for (auto component : m_mapComponent)
		Safe_Delete(component.second);

	m_mapComponent.clear();
}
