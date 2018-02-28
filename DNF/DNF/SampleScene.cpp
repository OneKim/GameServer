#include "stdafx.h"
#include "SampleScene.h"

CSampleScene::CSampleScene(void)
{
}

HRESULT CSampleScene::Initialize_Resource(void)
{
	return S_OK;
}

HRESULT CSampleScene::Initialize_Layer_Environment(void)
{
	return S_OK;
}

HRESULT CSampleScene::Initialize_Layer_GameLogic(void)
{
	return S_OK;
}

HRESULT CSampleScene::Initialize_Layer_UI(void)
{
	return S_OK;
}

HRESULT CSampleScene::Initialize_Scene(void)
{
	FAILED_CHECK(Initialize_Resource());
	FAILED_CHECK(Initialize_Layer_Environment());
	FAILED_CHECK(Initialize_Layer_GameLogic());
	FAILED_CHECK(Initialize_Layer_UI());

	return S_OK;
}

void CSampleScene::Update(const _float & fTimeDelta)
{
	CScene::Update(fTimeDelta);
}

void CSampleScene::Render(void)
{
	CScene::Render();
}

CSampleScene * CSampleScene::Create(void)
{
	CSampleScene* pInstance = new CSampleScene;

	if (FAILED(pInstance->Initialize_Scene()))
	{
		MSG_BOX(L"CSeriaRoom Created Failed");
		Safe_Delete(pInstance);
	}

	return pInstance;
}

CSampleScene::~CSampleScene(void)
{

}
