#include "stdafx.h"
#include "FrameMgr.h"
#include "Frame.h"

IMPLEMENT_SINGLETON(CFrameMgr)

CFrameMgr::CFrameMgr(void)
{
}

shared_ptr<CFrame> CFrameMgr::Find_Frame(const TCHAR * pFrameTag)
{
	MAPFRAME::iterator	iter = find_if(m_mapFrame.begin(), m_mapFrame.end(), CTagFinder(pFrameTag));

	if(iter == m_mapFrame.end())
		return NULL;

	return iter->second;
}

HRESULT CFrameMgr::Initialize_Frames(const TCHAR * pFrameTag, const _float & fLimitCall)
{
	NULL_CHECK_RETURN_MSG(!Find_Frame(pFrameTag), E_FAIL, L"Already SameTag Frame exist");

	m_mapFrame.insert(pair<const TCHAR*, shared_ptr<CFrame>>(pFrameTag, CFrame::Create(fLimitCall)));

	return S_OK;
}

_bool CFrameMgr::Is_Call(const TCHAR * pFrameTag, const _float & fTimeDelta)
{
	shared_ptr<CFrame>	pFrame = Find_Frame(pFrameTag);

	if (NULL == pFrame)
		return false;

	return pFrame->Is_Call(fTimeDelta);
}

CFrameMgr::~CFrameMgr(void)
{
	m_mapFrame.clear();
}
