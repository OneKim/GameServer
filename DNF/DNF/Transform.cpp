#include "stdafx.h"
#include "Transform.h"

CTransform::CTransform(const _vec3& vLook)
	: m_vPos(0.f, 0.f, 0.f)
	, m_vScale(1.f, 1.f, 1.f)
	, m_vDir(vLook)
{
	m_matWorld.Identity();
	m_matScale.Identity();
	m_matRot.Identity();
	m_matTrans.Identity();
	ZeroMemory(m_fAngle, sizeof(m_fAngle));
}

void CTransform::Update(void)
{
	m_matScale.Scaling(m_vScale.x, m_vScale.y, m_vScale.z);
	m_matRot.Identity();
	m_matRot.RotationX(m_fAngle[ANGLE_X]);
	m_matRot.RotationY(m_fAngle[ANGLE_Y]);
	m_matRot.RotationZ(m_fAngle[ANGLE_Z]);
	m_matTrans.Translation(m_vPos.x, m_vPos.y, m_vPos.z);
	m_matWorld = m_matScale * m_matRot * m_matTrans;

	memcpy(&m_vDir, &m_matWorld.m[2][0], sizeof(_vec3));
	m_vDir.Normalize();
}

void CTransform::Go_Straight(const _float& fSpeed)
{
	m_vPos += m_vDir * fSpeed;
}

CTransform* CTransform::Create(const _vec3& vLook)
{
	return new CTransform(vLook);
}

CTransform::~CTransform(void)
{

}
