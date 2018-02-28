#pragma once

class CDelete_Single
{
public:
	explicit CDelete_Single(void) {}
	~CDelete_Single(void) {}
public:
	template <typename T> void operator () (T& pInstance)
	{
		if (NULL != pInstance)
		{
			delete pInstance;
			pInstance = NULL;
		}
	}
};

class CDelete_Pair
{
public:
	explicit CDelete_Pair(void) {}
	~CDelete_Pair(void) {}
public:
	template <typename T> void operator () (T& Pair)
	{
		if (NULL != Pair.second)
		{
			delete Pair.second;
			Pair.second = NULL;
		}
	}
};

class CRelease_Single
{
public:
	explicit CRelease_Single(void) {}
	~CRelease_Single(void) {}
public:
	template <typename T> void operator () (T& pInstance)
	{
		if (NULL != pInstance)
		{			
			_ulong dwRefCnt = pInstance->Release();
			if (dwRefCnt == 0)
				pInstance = NULL;
		}
	}
};

class CClear_Pair
{
public:
	explicit CClear_Pair(void) {}
	~CClear_Pair(void) {}
public:
	template <typename T> void operator () (T& Pair)
	{
		Pair.second.clear();			
	}
};

class CTagFinder
{
private:
	const TCHAR*				m_pTag;
public:
	explicit CTagFinder(const TCHAR* pTag) : m_pTag(pTag) {}
	~CTagFinder(void) {}
public:
	template <typename T> bool operator () (T& Pair)
	{
		if (0 == lstrcmp(m_pTag, Pair.first))
			return true;
		else
			return false;
	}
};

class CStrCmp
{
private:
	const TCHAR*		m_pTag;
public:
	explicit CStrCmp(const TCHAR* pTag) :m_pTag(pTag) {}
	~CStrCmp(void) {}
public:
	bool	operator() (const TCHAR* pStr)
	{
		if (0 == lstrcmp(m_pTag, pStr))
			return true;
		else
			return false;
	}
};