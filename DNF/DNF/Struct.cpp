#include "stdafx.h"
#include "Struct.h"

_vec2::_vec2(CONST FLOAT * p)
	: D3DXVECTOR2(p)
{

}

_vec2::_vec2(CONST D3DXFLOAT16 * p)
	: D3DXVECTOR2(p)
{

}

_vec2::_vec2(FLOAT x, FLOAT y)
	: D3DXVECTOR2(x, y)
{

}

_vec3::_vec3(CONST FLOAT *pFloat)
	: D3DXVECTOR3(pFloat)
{

}

_vec3::_vec3(CONST D3DVECTOR& v)
	: D3DXVECTOR3(v)
{

}

_vec3::_vec3(CONST D3DXFLOAT16 *pFloat)
	: D3DXVECTOR3(pFloat)
{

}

_vec3::_vec3(FLOAT x, FLOAT y, FLOAT z)
	: D3DXVECTOR3(x, y, z)
{

}

_vec3* _vec3::Normalize(void)
{
	D3DXVec3Normalize(this, this);
	return this;
}

float _vec3::Length(void) const
{
	return D3DXVec3Length(this);
}

float _vec3::Dot(const D3DXVECTOR3* vDst) const
{
	return D3DXVec3Dot(this, vDst);
}

_vec3 _vec3::Cross(const D3DXVECTOR3* vDst, bool bInv /*= false*/)
{
	_vec3 vOut;
	if (bInv == false)
		D3DXVec3Cross(&vOut, this, vDst);
	else
		D3DXVec3Cross(&vOut, vDst, this);

	return vOut;
}

_vec3* _vec3::TransformCoord(const D3DXMATRIX* pMat)
{
	D3DXVec3TransformCoord(this, this, pMat);
	return this;
}

_vec3* _vec3::TransformNormal(const D3DXMATRIX* pMat)
{
	D3DXVec3TransformNormal(this, this, pMat);
	return this;
}


_vec4::_vec4(CONST FLOAT* p)
	: D3DXVECTOR4(p)
{

}

_vec4::_vec4(CONST D3DXFLOAT16* p)
	: D3DXVECTOR4(p)
{

}

_vec4::_vec4(CONST D3DVECTOR& xyz, FLOAT w)
	: D3DXVECTOR4(xyz, w)
{

}

_vec4::_vec4(FLOAT x, FLOAT y, FLOAT z, FLOAT w)
	: D3DXVECTOR4(x, y, z, w)
{

}

_vec4* _vec4::Normalize(void)
{
	D3DXVec4Normalize(this, this);
	return this;
}

float _vec4::Length(void) const
{
	return D3DXVec4Length(this);
}

_matrix::_matrix(CONST FLOAT *pFloat)
	: D3DXMATRIX(pFloat)
{

}

_matrix::_matrix(CONST D3DMATRIX& tMat)
	: D3DXMATRIX(tMat)
{

}

_matrix::_matrix(CONST D3DXFLOAT16 *pFloat)
	: D3DXMATRIX(pFloat)
{

}

_matrix::_matrix(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14, FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24, FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34, FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44)
	: D3DXMATRIX(_11, _12, _13, _14
		, _21, _22, _23, _24
		, _31, _32, _33, _34
		, _41, _42, _43, _44)
{

}

_matrix* _matrix::Identity(void)
{
	D3DXMatrixIdentity(this);
	return this;
}

_matrix* _matrix::Inverse(void)
{
	D3DXMatrixInverse(this, NULL, this);
	return this;
}

_matrix* _matrix::Scaling(const float& fX, const float& fY, const float& fZ)
{
	D3DXMatrixScaling(this, fX, fY, fZ);
	return this;
}

_matrix* _matrix::RotationAxis(const D3DXVECTOR3* pAxis, const float& fAngle)
{
	D3DXMatrixRotationAxis(this, pAxis, fAngle);
	return this;
}

_matrix* _matrix::RotationX(const float& fAngle)
{
	_matrix mat;
	D3DXMatrixRotationX(&mat, fAngle);
	*this *= mat;
	return this;
}

_matrix* _matrix::RotationY(const float& fAngle)
{
	_matrix mat;
	D3DXMatrixRotationY(&mat, fAngle);
	*this *= mat;
	return this;
}

_matrix* _matrix::RotationZ(const float& fAngle)
{
	_matrix mat;
	D3DXMatrixRotationZ(&mat, fAngle);
	*this *= mat;
	return this;
}

_matrix* _matrix::Translation(const float& fX, const float& fY, const float& fZ)
{
	D3DXMatrixTranslation(this, fX, fY, fZ);
	return this;
}