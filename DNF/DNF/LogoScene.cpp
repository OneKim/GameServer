#include "stdafx.h"
#include "LogoScene.h"

CLogoScene::CLogoScene(void)
{
}

HRESULT CLogoScene::Initialize_Resource(void)
{
	return S_OK;
}

HRESULT CLogoScene::Initialize_Layer_Environment(void)
{
	return S_OK;
}

HRESULT CLogoScene::Initialize_Layer_GameLogic(void)
{
	return S_OK;
}

HRESULT CLogoScene::Initialize_Layer_UI(void)
{
	return S_OK;
}

HRESULT CLogoScene::Initialize_Scene(void)
{
	FAILED_CHECK(Initialize_Resource());
	FAILED_CHECK(Initialize_Layer_Environment());
	FAILED_CHECK(Initialize_Layer_GameLogic());
	FAILED_CHECK(Initialize_Layer_UI());

	return S_OK;
}

void CLogoScene::Update(const _float & fTimeDelta)
{
	CScene::Update(fTimeDelta);
}

void CLogoScene::Render(void)
{
	CScene::Render();
}

CLogoScene * CLogoScene::Create(void)
{
	CLogoScene* pInstance = new CLogoScene;

	if (FAILED(pInstance->Initialize_Scene()))
	{
		MSG_BOX(L"CLogoScene Created Failed");
		Safe_Delete(pInstance);
	}

	return pInstance;
}

CLogoScene::~CLogoScene(void)
{

}
