#pragma once

#include "VIBuffer.h"

class CRcTex : public CVIBuffer
{
private:
	explicit CRcTex(void);
	explicit CRcTex(const CRcTex& Prototype);	
private:
	virtual HRESULT Create_Buffer(void);
public:
	virtual CResources* Clone_Resource(void);
public:
	static CRcTex* Create(void);
public:
	virtual ~CRcTex(void);
};