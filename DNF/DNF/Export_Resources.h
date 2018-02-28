#pragma once

#include "ResourceMgr.h"

namespace Engine
{
	/////////////////////////////////////////////////////////////
	//For.ResourceMgr

	// For.Getter
	inline const TCHAR*				Find_ResourceKey(const _ushort& wContainerIdx, const TCHAR* pResourceKey);
	inline CResources*				Clone_Resource(const _ushort& wContainerIdx, const TCHAR* pResourceKey);

	// For.Setter

	// For.General
	inline HRESULT	Add_Buffer(const _ushort& wContainerIdx, CVIBuffer::BUFFERTYPE eBufferType, const TCHAR* pResourceKey, const _ushort& wCntX = 0, const _ushort& wCntZ = 0, const _ushort& wItv = 1);
	inline HRESULT	Add_Texture(const _ushort& wContainerIdx, const TCHAR* pResourceKey, const TCHAR* pFilePath, const _ushort& wCnt = 1);
	inline void		Reserve_ContainerSize(const _ushort& nSize);	
	inline void		Reset_Resource(const _ushort& wContainerIdx);

	/////////////////////////////////////////////////////////////
	//For.Release
	inline void Release_Resources(void);

#include "Export_Resources.inl"

}