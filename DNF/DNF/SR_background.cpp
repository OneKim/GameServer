#include "stdafx.h"
#include "SR_background.h"
#include "Transform.h"

CSR_background::CSR_background(void)
	: m_pTransCom(NULL)
	, m_pBufferCom(NULL)
	, m_pTextureCom(NULL)
{

}

HRESULT CSR_background::AddComponent(void)
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
	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Resource(RESOURCE_STATIC, L"Texture_SeriaRoom"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent.insert(make_pair(L"Com_Texture", dynamic_cast<CComponent*>(m_pTextureCom)));

	return S_OK;
}

HRESULT CSR_background::Initialize_GameObject(void)
{
	FAILED_CHECK(this->AddComponent());

	m_pTransCom->m_vScale = _vec3(WINSIZEX, WINSIZEY, 1.f);	

	return S_OK;
}

void CSR_background::Update(const _float& fTimeDelta)
{
	CGameObject::Update(fTimeDelta);
	Engine::Add_RenderGroup(CRenderer::TYPE_PRIORITY, this);
}

void CSR_background::Render(void)
{	
	m_pTextureCom->Render_Texture(0);
	m_pBufferCom->Render_Buffer(&m_pTransCom->m_matWorld);
}

CGameObject* CSR_background::Create(void)
{
	CGameObject* pInstance = new CSR_background;
	if (FAILED(pInstance->Initialize_GameObject())) {
		MSG_BOX(L"CSR_background Created Failed");
		Safe_Delete(pInstance);
	}
	return pInstance;
}

CSR_background::~CSR_background(void)
{

}