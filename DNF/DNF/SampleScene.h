#pragma once

#include "Scene.h"

class CSampleScene : public CScene
{
private:
	explicit	CSampleScene(void);
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
	static CSampleScene* Create(void);
public:
	virtual ~CSampleScene(void);
};