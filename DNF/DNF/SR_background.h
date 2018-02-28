#pragma once

#include "GameObject.h"

class CTexture;
class CTransform;
class CSR_background : public CGameObject
{
private:
	CTransform*	m_pTransCom;
	CVIBuffer*	m_pBufferCom;
	CTexture*	m_pTextureCom;
private:
	explicit CSR_background(void);
protected:
	virtual HRESULT AddComponent(void);
public:
	virtual HRESULT Initialize_GameObject(void);
	virtual void Update(const _float& fTimeDelta);
	virtual void Render(void);
public:
	static CGameObject* Create(void);
public:
	virtual ~CSR_background(void);

};