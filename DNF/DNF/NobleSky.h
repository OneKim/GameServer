#pragma once

#include "Scene.h"

class CNobleSky : public CScene
{
private:
	explicit	CNobleSky(void);
private:
	virtual HRESULT Initialize_Resource(void);
	virtual HRESULT Initialize_Layer_Environment(void);
	virtual HRESULT Initialize_Layer_GameLogic(void);
	virtual HRESULT Initialize_Layer_UI(void);
public:
	virtual HRESULT	Initialize_Scene(void);
	virtual void	Update(const _float& fTimeDelta);
	virtual void	Render(void);
public:
	static CNobleSky* Create(void);
public:
	virtual ~CNobleSky(void);
};