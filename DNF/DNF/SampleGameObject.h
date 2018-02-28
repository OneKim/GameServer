#pragma once

#include "GameObject.h"

class CSampleGameObject : public CGameObject
{
private:
	explicit CSampleGameObject(void);
protected:
	virtual HRESULT AddComponent(void);
public:
	virtual HRESULT Initialize_GameObject(void);
	virtual void Update(const _float& fTimeDelta);
	virtual void Render(void);
public:
	static CGameObject* Create(void);
public:
	virtual ~CSampleGameObject(void);

};