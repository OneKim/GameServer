#include "stdafx.h"
#include "NobleSky.h"

CNobleSky::CNobleSky(void)
{
}

HRESULT CNobleSky::Initialize_Resource(void)
{
	return S_OK;
}

HRESULT CNobleSky::Initialize_Layer_Environment(void)
{
	return S_OK;
}

HRESULT CNobleSky::Initialize_Layer_GameLogic(void)
{
	return S_OK;
}

HRESULT CNobleSky::Initialize_Layer_UI(void)
{
	return S_OK;
}

HRESULT CNobleSky::Initialize_Scene(void)
{
	return S_OK;
}

void CNobleSky::Update(const _float & fTimeDelta)
{
	CScene::Update(fTimeDelta);
}

void CNobleSky::Render(void)
{
	CScene::Render();
}

CNobleSky* CNobleSky::Create(void)
{
	CNobleSky* pInstance = new CNobleSky;

	if (FAILED(pInstance->Initialize_Scene()))
	{
		MSG_BOX(L"CNobleSky Created Failed");
		Safe_Delete(pInstance);
	}

	return pInstance;
}

CNobleSky::~CNobleSky(void)
{

}
