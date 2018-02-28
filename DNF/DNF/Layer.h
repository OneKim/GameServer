#pragma once

class CGameObject;
class CComponent;
class CLayer
{
private:
	typedef list<CGameObject*>				OBJECTLIST;
	typedef map<const TCHAR*, OBJECTLIST> MAPOBJLIST;
private:
	MAPOBJLIST		m_mapObjlist;
private:
	explicit	CLayer(void);
public:
	void		Update(const _float& fTimeDelta);
	void		Render(void);
public:	
	OBJECTLIST*  Get_ObjList(const TCHAR* pObjectKey);
	CGameObject*	Get_Object(const TCHAR* pObjectKey, _ulong dwIndex);
	CComponent*	Get_Component(const TCHAR* pObjectKey, const TCHAR* pComKey, _ulong dwIndex);
	HRESULT		 Add_Object(const TCHAR* pObjectKey, CGameObject* pGameObject);
public:
	static CLayer* Create(void);
public:
	virtual ~CLayer(void);
};