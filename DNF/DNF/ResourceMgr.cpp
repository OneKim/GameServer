#include "stdafx.h"
#include "ResourceMgr.h"
#include "RcTex.h"
#include "Texture.h"

IMPLEMENT_SINGLETON(CResourceMgr)

CResourceMgr::CResourceMgr(void)
	: m_pmapResource(NULL)
	, m_wReservedSize(0)
{
}

void CResourceMgr::Add_ResourceKey(const _ushort & wContainerIdx, const TCHAR * pResourceKey)
{
	MAPKEY::iterator iter = m_mapKey.find(wContainerIdx);
	if (iter == m_mapKey.end())
		m_mapKey.insert(MAPKEY::value_type(wContainerIdx, list<const TCHAR*>()));

	list<const TCHAR*>::iterator iterList = find_if(m_mapKey[wContainerIdx].begin(), m_mapKey[wContainerIdx].end(), CStrCmp(pResourceKey));
	if (iterList == m_mapKey[wContainerIdx].end())
		m_mapKey[wContainerIdx].push_back(pResourceKey);
}

CResources* CResourceMgr::Find_Resource(const _ushort & wContainerIdx, const TCHAR * pResourceKey)
{
	MAPRESOURCE::iterator	iter = find_if(m_pmapResource[wContainerIdx].begin(), m_pmapResource[wContainerIdx].end(), CTagFinder(pResourceKey));

	if(iter == m_pmapResource[wContainerIdx].end())
		return NULL;

	return iter->second;
}

const TCHAR * CResourceMgr::Find_ResourceKey(const _ushort & wContainerIdx, const TCHAR * pResourceKey)
{
	MAPKEY::iterator iterMap = m_mapKey.find(wContainerIdx);
	if (iterMap == m_mapKey.end())
		return NULL;

	list<const TCHAR*>::iterator iter = find_if(iterMap->second.begin(), iterMap->second.end(), CStrCmp(pResourceKey));
	if (iter == iterMap->second.end())
		return NULL;

	return (*iter);
}

CResources* CResourceMgr::Clone_Resource(const _ushort & wContainerIdx, const TCHAR * pResourceKey)
{
	CResources* pResource = Find_Resource(wContainerIdx, pResourceKey);
	NULL_CHECK_RETURN(pResource, NULL);

	return pResource->Clone_Resource();
}

HRESULT CResourceMgr::Add_Buffer(const _ushort & wContainerIdx, CVIBuffer::BUFFERTYPE eBufferType, const TCHAR * pResourceKey, const _ushort & wCntX, const _ushort & wCntZ, const _ushort & wItv)
{
	NULL_CHECK_RETURN_MSG(m_wReservedSize, E_FAIL, L"ReservedSize Not Failed");
	NULL_CHECK_RETURN_MSG(m_pmapResource, E_FAIL, L"pmapResource Not Failed");

	CResources* pResource = Find_Resource(wContainerIdx, pResourceKey);

	NULL_CHECK_RETURN_TAGMSG(!pResource, E_FAIL, pResourceKey, L"Already Buffer Exist!");

	CVIBuffer*		pBuffer = NULL;

	switch (eBufferType)
	{
	case CVIBuffer::BUFFER_RCTEX:
		pBuffer = CRcTex::Create();
		break;
	}

	NULL_CHECK_RETURN(pBuffer, E_FAIL);

	m_pmapResource[wContainerIdx].insert(MAPRESOURCE::value_type(pResourceKey, pBuffer));

	Add_ResourceKey(wContainerIdx, pResourceKey);

	return S_OK;
}

HRESULT CResourceMgr::Add_Texture(const _ushort & wContainerIdx, const TCHAR * pResourceKey, const TCHAR * pFilePath, const _ushort & wCnt)
{
	NULL_CHECK_RETURN_MSG(m_wReservedSize, E_FAIL, L"ReservedSize Not Failed");
	NULL_CHECK_RETURN_MSG(m_pmapResource, E_FAIL, L"pmapResource Not Failed");

	CResources* pResource = Find_Resource(wContainerIdx, pResourceKey);

	NULL_CHECK_RETURN_TAGMSG(!pResource, E_FAIL, pResourceKey, L"Already Texture Exist!");

	pResource = CTexture::Create(pFilePath, wCnt);
	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_pmapResource[wContainerIdx].insert(MAPRESOURCE::value_type(pResourceKey, pResource));

	Add_ResourceKey(wContainerIdx, pResourceKey);

	return S_OK;
}

HRESULT CResourceMgr::Reserve_ContainerSize(const _ushort & wSize)
{
	if (m_wReservedSize != 0 || m_pmapResource != NULL)
		return E_FAIL;

	m_pmapResource = new MAPRESOURCE[wSize];

	m_wReservedSize = wSize;

	return S_OK;
}

void CResourceMgr::Reset_Resource(const _ushort & wContainerIdx)
{
	m_pmapResource[wContainerIdx].clear();

	MAPKEY::iterator iter = m_mapKey.find(wContainerIdx);
	if (iter != m_mapKey.end())
	{
		m_mapKey[wContainerIdx].clear();
	}
}

CResourceMgr::~CResourceMgr(void)
{
	for (_ushort i = 0; i < m_wReservedSize; ++i)
	{
		for (auto resource : m_pmapResource[i])
			Safe_Delete(resource.second);
	}		

	Safe_Delete_Array(m_pmapResource);
}
