#pragma once

class CComponent;
class CGameObject
{
protected:
	typedef map<const TCHAR*, CComponent*>		MAPCOMPONENT;	
protected:
	MAPCOMPONENT		m_mapComponent;
	_float				m_fViewZ;
	_float				m_fTimeDelta;
protected:
	explicit	CGameObject();
protected:
	virtual HRESULT AddComponent(void);
protected:
	void Compute_ViewZ(const _vec3* pPosition);
public:
	virtual HRESULT	Initialize_GameObject(void);
	virtual void Update(const _float& fTimeDelta);
	virtual void Render(void);
public:
	CComponent*		Get_Component(const TCHAR* pComKey);
	const _float&	Get_ViewZ(void);
public:
	virtual ~CGameObject(void);
};