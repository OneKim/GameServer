#pragma once

template <typename T> void Safe_Delete(T& pointer)
{
	if (NULL != pointer)
	{
		delete pointer;
		pointer = NULL;
	}
}

template <typename T> void Safe_Delete_Array(T& pointer)
{
	if (NULL != pointer)
	{
		delete[] pointer;
		pointer = NULL;
	}
}

template <typename T> void Safe_Release(T& pointer)
{
	if (NULL != pointer)
	{
		_ulong dwRefCnt = pointer->Release();
		if (dwRefCnt == 0)
			pointer = NULL;
	}
}

//------------------------------------------------------------------------//
//문자열 변환

inline void StrConvA2W(const CHAR *src, WCHAR *dest, size_t destLen) {
	if (destLen < 1) {
		return;
	}
	MultiByteToWideChar(CP_ACP, 0, src, -1, dest, (int)destLen - 1);
}

inline void StrConvW2A(const WCHAR * src, CHAR *dest, size_t destLen) {
	if (destLen < 1) {
		return;
	}
	WideCharToMultiByte(CP_ACP, 0, src, -1, dest, (int)destLen, NULL, FALSE);
}