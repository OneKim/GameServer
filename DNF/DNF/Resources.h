#pragma once

#include "Component.h"

class CResources : public CComponent
{
protected:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
protected:
	explicit CResources(void);
	explicit CResources(const CResources& Prototype);
public:
	virtual CResources* Clone_Resource(void) PURE;
public:
	virtual ~CResources(void);
};