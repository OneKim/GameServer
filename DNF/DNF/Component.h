#pragma once

class CComponent abstract
{
protected:
	explicit CComponent(void);	
public:
	virtual void Update(void);
public:
	virtual ~CComponent(void);
};