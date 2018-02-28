#include "stdafx.h"
#include "Player.h"
#include "Transform.h"

CPlayer::CPlayer(void)
	: m_pTransCom(NULL)
	, m_pBufferCom(NULL)
	, m_pTextureCom(NULL)
	, m_fSpeedX(0.f)
	, m_fSpeedY(0.f)
{

}

HRESULT CPlayer::AddComponent(void)
{
	//For. Transform Component
	m_pTransCom = CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent.insert(make_pair(L"Com_Trans", dynamic_cast<CComponent*>(m_pTransCom)));

	//For. Buffer Component
	m_pBufferCom = dynamic_cast<CVIBuffer*>(Engine::Clone_Resource(RESOURCE_STATIC, L"Buffer_RcTex"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent.insert(make_pair(L"Com_Buffer", dynamic_cast<CComponent*>(m_pBufferCom)));

	//For. Texture Componet
	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Resource(RESOURCE_STATIC, L"Texture_Player"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent.insert(make_pair(L"Com_Texture", dynamic_cast<CComponent*>(m_pTextureCom)));

	return S_OK;
}

HRESULT CPlayer::Initialize_GameObject(void)
{
	FAILED_CHECK(this->AddComponent());

	m_pTransCom->m_vScale = _vec3(210.f, 240.f, 1.f);
	m_fSpeedX = 200.f;
	m_fSpeedY = 150.f;

	return S_OK;
}

void CPlayer::Check_KeyState(const _float& fTimeDelta)
{
	if (Engine::Get_DIKeyState(DIK_UP)) {
		m_pTransCom->m_vPos.y += m_fSpeedY * fTimeDelta;
	}

	if (Engine::Get_DIKeyState(DIK_DOWN)) {
		m_pTransCom->m_vPos.y -= m_fSpeedY * fTimeDelta;
	}

	if (Engine::Get_DIKeyState(DIK_LEFT)) {
		m_pTransCom->m_vPos.x -= m_fSpeedX * fTimeDelta;
	}

	if (Engine::Get_DIKeyState(DIK_RIGHT)) {
		m_pTransCom->m_vPos.x += m_fSpeedX * fTimeDelta;
	}
}

void CPlayer::Update(const _float& fTimeDelta)
{
	Check_KeyState(fTimeDelta);
	CGameObject::Update(fTimeDelta);
	Engine::Add_RenderGroup(CRenderer::TYPE_ALPHA, this);
}

void CPlayer::Render(void)
{	
	m_pTextureCom->Render_Texture(0);
	m_pBufferCom->Render_Buffer(&m_pTransCom->m_matWorld);
}

CGameObject* CPlayer::Create(void)
{
	CGameObject* pInstance = new CPlayer;
	if (FAILED(pInstance->Initialize_GameObject())) {
		MSG_BOX(L"CPlayer Created Failed");
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CPlayer::~CPlayer(void)
{

}
