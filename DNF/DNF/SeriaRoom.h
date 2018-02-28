#pragma once

#include "Scene.h"

class CSeriaRoom : public CScene
{
private:
	explicit	CSeriaRoom(void);
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
	static CSeriaRoom* Create(void);
public:
	virtual ~CSeriaRoom(void);
};