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