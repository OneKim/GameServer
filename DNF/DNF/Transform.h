#pragma once

#include "Component.h"

class CTransform : public CComponent
{
public:
	enum ANGLE { ANGLE_X, ANGLE_Y, ANGLE_Z, ANGLE_END };
public:	
	_matrix		m_matWorld;
	_matrix		m_matScale;
	_matrix		m_matRot;
	_matrix		m_matTrans;
	_vec3		m_vPos;
	_vec3		m_vScale;
	_vec3		m_vDir;
	_float		m_fAngle[ANGLE_END];	
private:
	explicit CTransform(const _vec3& vLook);	
public:
	virtual	void Update(void);
public:
	void Go_Straight(const _float& fSpeed);	
public:
	static CTransform* Create(const _vec3& vLook);
	virtual ~CTransform(void);
};