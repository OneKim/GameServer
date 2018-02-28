#include "stdafx.h"
#include "SampleGameObject.h"

CSampleGameObject::CSampleGameObject(void)
{

}

HRESULT CSampleGameObject::AddComponent(void)
{
	return S_OK;
}

HRESULT CSampleGameObject::Initialize_GameObject(void)
{	
	FAILED_CHECK(this->AddComponent());
	return S_OK;
}

void CSampleGameObject::Update(const _float& fTimeDelta)
{
	CGameObject::Update(fTimeDelta);
}

void CSampleGameObject::Render(void)
{

}

CGameObject* CSampleGameObject::Create(void)
{
	CGameObject* pInstance = new CSampleGameObject;
	if (FAILED(pInstance->Initialize_GameObject())) {
		MSG_BOX(L"CSampleGameObject Created Failed");
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CSampleGameObject::~CSampleGameObject(void)
{

}
