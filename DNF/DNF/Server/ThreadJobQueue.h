#pragma once

#include "stdafx.h"
#include <queue>

template<typename T>
class ThreadJobQueue
{
private:
	enum { WRITE_QUEUE, READ_QUEUE, MAX_QUEUE };

	queue<T>			m_Queue[MAX_QUEUE];
	queue<T>*			m_WriteQueue;
	queue<T>*			m_ReadQueue;

	CRITICAL_SECTION	m_CSKey;

public:
	ThreadJobQueue(void)
	{
		m_WriteQueue = &m_Queue[WRITE_QUEUE];
		m_ReadQueue = &m_Queue[READ_QUEUE];

		InitializeCriticalSection(&m_CSKey);
	}
	~ThreadJobQueue(void)
	{
		DeleteCriticalSection(&m_CSKey);
	}

	inline void push(const T &t)
	{
		EnterCriticalSection(&m_CSKey);

		m_WriteQueue->push(t);

		LeaveCriticalSection(&m_CSKey);
	}
	inline bool pop(T &t)
	{
		EnterCriticalSection(&m_CSKey);		

		size_t size = m_Queue[WRITE_QUEUE].size() + m_Queue[READ_QUEUE].size();
		if (0 == size) {
			LeaveCriticalSection(&m_CSKey);
			return false;
		}			
		if (m_ReadQueue->empty()) this->swap();
		t = m_ReadQueue->front();
		m_ReadQueue->pop();

		LeaveCriticalSection(&m_CSKey);
		return true;		
	}

	inline void swap()
	{
		if (m_WriteQueue == &m_Queue[WRITE_QUEUE]) {
			m_WriteQueue = &m_Queue[READ_QUEUE];
			m_ReadQueue = &m_Queue[WRITE_QUEUE];
		}
		else {
			m_WriteQueue = &m_Queue[WRITE_QUEUE];
			m_ReadQueue = &m_Queue[READ_QUEUE];
		}
	}	
};