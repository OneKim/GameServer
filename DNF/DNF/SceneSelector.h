#pragma once

#include "Scene.h"
#include "Loading.h"
#include "LogoScene.h"
#include "SeriaRoom.h"
#include "NobleSky.h"

class CSceneSelector
{
public:

public:
	explicit CSceneSelector(SCENE eSceneID, CLoading::LOADINGTYPE eLoadingType = CLoading::LOADING_END)
		: m_eSceneID(eSceneID)
		, m_eLoadingType(eLoadingType)
	{}
	~CSceneSelector(void) {}
public:
	HRESULT operator () (CScene** ppScene)
	{
		switch (m_eSceneID)
		{
		case SCENE_LOGO:
			*ppScene = CLogoScene::Create();
			break;
		case SCENE_SR:
			*ppScene = CSeriaRoom::Create();
			break;
		case SCENE_NS:
			*ppScene = CNobleSky::Create();
			break;
		}

		if (NULL == *ppScene)
			return E_FAIL;

		return S_OK;
	}
private:
	SCENE					m_eSceneID;
	CLoading::LOADINGTYPE	m_eLoadingType;
};