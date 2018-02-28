#pragma once

#include "GameObject.h"

class CTransform;
class CPlayer : public CGameObject
{
private:
	CTransform* m_pTransCom;
	CVIBuffer*	m_pBufferCom;
	CTexture*	m_pTextureCom;
private:
	_float		m_fSpeedX;
	_float		m_fSpeedY;
private:
	explicit CPlayer(void);
protected:
	virtual HRESULT AddComponent(void);
private:
	void	Check_KeyState(const _float& fTimeDelta);
public:
	virtual HRESULT Initialize_GameObject(void);
	virtual void Update(const _float& fTimeDelta);
	virtual void Render(void);
public:
	static CGameObject* Create(void);
public:
	virtual ~CPlayer(void);

};