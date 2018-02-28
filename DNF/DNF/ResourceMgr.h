#pragma once

#include "VIBuffer.h"
#include "Texture.h"

class CResourceMgr
{
	DECLARE_SINGLETON(CResourceMgr)
private:
	typedef map<const TCHAR*, CResources*>	MAPRESOURCE;
	typedef map<_ushort, list<const TCHAR*>>			MAPKEY;
	MAPRESOURCE*		m_pmapResource;
	_ushort				m_wReservedSize;
	MAPKEY				m_mapKey;	
private:
	explicit CResourceMgr(void);
private:
	void	Add_ResourceKey(const _ushort& wContainerIdx, const TCHAR* pResourceKey);
	CResources*	Find_Resource(const _ushort& wContainerIdx, const TCHAR* pResourceKey);
public:	
	const TCHAR*			Find_ResourceKey(const _ushort& wContainerIdx, const TCHAR* pResourceKey);
	CResources*	Clone_Resource(const _ushort& wContainerIdx, const TCHAR* pResourceKey);	
public:
	HRESULT Add_Buffer(const _ushort& wContainerIdx, CVIBuffer::BUFFERTYPE eBufferType, const TCHAR* pResourceKey, const _ushort& wCntX = 0, const _ushort& wCntZ = 0, const _ushort& wItv = 1);
	HRESULT Add_Texture(const _ushort& wContainerIdx, const TCHAR* pResourceKey, const TCHAR* pFilePath, const _ushort& wCnt = 1);
	HRESULT Reserve_ContainerSize(const _ushort& wSize);
	void	Reset_Resource(const _ushort& wContainerIdx);
public:
	~CResourceMgr(void);
};