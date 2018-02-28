#include "stdafx.h"
#include "Resources.h"

CResources::CResources(void)
	: m_pGraphicDev(Engine::Get_GraphicDev())
{
}

CResources::CResources(const CResources& Prototype)
	: m_pGraphicDev(Prototype.m_pGraphicDev)
{
}

CResources * CResources::Clone_Resource(void)
{
	return nullptr;
}

CResources::~CResources(void)
{
}
