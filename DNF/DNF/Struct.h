#pragma once

typedef struct _vec2 : public D3DXVECTOR2
{
	_vec2() {};
	_vec2(CONST FLOAT * p);
	_vec2(CONST D3DXFLOAT16 * p);
	_vec2(FLOAT x, FLOAT y);

	_vec2* Normalize(void);
	float  Length(void) const;

}_vec2;

typedef struct _vec3 : public D3DXVECTOR3
{
	_vec3() {};
	_vec3(CONST FLOAT *);
	_vec3(CONST D3DVECTOR&);
	_vec3(CONST D3DXFLOAT16 *);
	_vec3(FLOAT x, FLOAT y, FLOAT z);

	_vec3* Normalize(void);
	float  Length(void) const;

	float  Dot(const D3DXVECTOR3* vDst) const;
	_vec3  Cross(const D3DXVECTOR3* vDst, bool bInv = false);
	_vec3* TransformCoord(const D3DXMATRIX* pMat);
	_vec3* TransformNormal(const D3DXMATRIX* pMat);

}_vec3;

typedef struct _vec4 : public D3DXVECTOR4
{
	_vec4() {};
	_vec4(CONST FLOAT* p);
	_vec4(CONST D3DXFLOAT16* p);
	_vec4(CONST D3DVECTOR& xyz, FLOAT w);
	_vec4(FLOAT x, FLOAT y, FLOAT z, FLOAT w);

	_vec4* Normalize(void);
	float  Length(void) const;
}_vec4;

typedef struct _matrix : public D3DXMATRIX
{
	_matrix() {};
	_matrix(CONST FLOAT *);
	_matrix(CONST D3DMATRIX&);
	_matrix(CONST D3DXFLOAT16 *);
	_matrix(FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
		FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
		FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
		FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44);

	_matrix*	Identity(void);
	_matrix*	Inverse(void);
	_matrix*	Scaling(const float& fX, const float& fY, const float& fZ);
	_matrix*	RotationAxis(const D3DXVECTOR3* pAxis, const float& fAngle);
	_matrix*	RotationX(const float& fAngle);
	_matrix*	RotationY(const float& fAngle);
	_matrix*	RotationZ(const float& fAngle);
	_matrix*	Translation(const float& fX, const float& fY, const float& fZ);
}_matrix;

typedef struct tagVertexTexture
{
	_vec3				vPos;
	_vec3				vNormal;
	_vec2				vTexUV;
}VTXTEX;

const _ulong VTXFVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

typedef struct tagIndex16
{
	_ushort			_1, _2, _3;
}INDEX16;