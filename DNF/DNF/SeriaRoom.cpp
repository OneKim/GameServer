#include "stdafx.h"
#include "SeriaRoom.h"
#include "SR_background.h"
#include "Player.h"

CSeriaRoom::CSeriaRoom(void)
{
}

HRESULT CSeriaRoom::Initialize_Resource(void)
{
	return S_OK;
}

HRESULT CSeriaRoom::Initialize_Layer_Environment(void)
{
	CLayer* pLayer				= CLayer::Create();
	CGameObject* pGameObject	= NULL;

	//background
	pGameObject = CSR_background::Create();
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->Add_Object(L"Obj_background", pGameObject);

	m_mapLayer.insert(make_pair(L"Layer_Environment", pLayer));

	return S_OK;
}

HRESULT CSeriaRoom::Initialize_Layer_GameLogic(void)
{
	CLayer* pLayer = CLayer::Create();
	CGameObject* pGameObject = NULL;

	//Player
	pGameObject = CPlayer::Create();
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->Add_Object(L"Obj_Player", pGameObject);

	m_mapLayer.insert(make_pair(L"Layer_GameLogic", pLayer));

	return S_OK;
}

HRESULT CSeriaRoom::Initialize_Layer_UI(void)
{
	return S_OK;
}

HRESULT CSeriaRoom::Initialize_Scene(void)
{
	FAILED_CHECK(Initialize_Resource());
	FAILED_CHECK(Initialize_Layer_Environment());
	FAILED_CHECK(Initialize_Layer_GameLogic());
	FAILED_CHECK(Initialize_Layer_UI());

	return S_OK;
}

void CSeriaRoom::Update(const _float & fTimeDelta)
{
	CScene::Update(fTimeDelta);
}

void CSeriaRoom::Render(void)
{
	CScene::Render();
}

CSeriaRoom * CSeriaRoom::Create(void)
{
	CSeriaRoom* pInstance = new CSeriaRoom;

	if (FAILED(pInstance->Initialize_Scene()))
	{
		MSG_BOX(L"CSeriaRoom Created Failed");
		Safe_Delete(pInstance);
	}

	return pInstance;
}

CSeriaRoom::~CSeriaRoom(void)
{

}
