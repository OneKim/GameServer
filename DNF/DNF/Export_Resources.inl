/////////////////////////////////////////////////////////////
//For.ResourceMgr

// For.Getter
const TCHAR* Engine::Find_ResourceKey(const _ushort& wContainerIdx, const TCHAR* pResourceKey)
{
	return CResourceMgr::Get_Instance()->Find_ResourceKey(wContainerIdx, pResourceKey);
}

CResources* Engine::Clone_Resource(const _ushort& wContainerIdx, const TCHAR* pResourceKey)
{
	return CResourceMgr::Get_Instance()->Clone_Resource(wContainerIdx, pResourceKey);
}

// For.Setter

// For.General
HRESULT Engine::Add_Buffer(const _ushort& wContainerIdx, CVIBuffer::BUFFERTYPE eBufferType, const TCHAR* pResourceKey, const _ushort& wCntX, const _ushort& wCntZ, const _ushort& wItv)
{
	return CResourceMgr::Get_Instance()->Add_Buffer(wContainerIdx, eBufferType, pResourceKey, wCntX, wCntZ, wItv);
}

HRESULT Engine::Add_Texture(const _ushort& wContainerIdx, const TCHAR* pResourceKey, const TCHAR* pFilePath, const _ushort& wCnt)
{
	return CResourceMgr::Get_Instance()->Add_Texture(wContainerIdx, pResourceKey, pFilePath, wCnt);
}

void Engine::Reserve_ContainerSize(const _ushort& nSize)
{
	CResourceMgr::Get_Instance()->Reserve_ContainerSize(nSize);
}

void Engine::Reset_Resource(const _ushort& wContainerIdx)
{
	return CResourceMgr::Get_Instance()->Reset_Resource(wContainerIdx);
}

/////////////////////////////////////////////////////////////
//For.Release
void Engine::Release_Resources(void)
{
	CResourceMgr::Get_Instance().~shared_ptr();
}