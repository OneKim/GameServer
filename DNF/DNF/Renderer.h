#pragma once

class CScene;
class CGameObject;

class CRenderer
{
public:
	enum RENDERGROUP { TYPE_PRIORITY, TYPE_NONEALPHA, TYPE_ALPHA, TYPE_UI, TYPE_END	};
private:
	typedef list<CGameObject*>				RENDERLIST;
	RENDERLIST								m_RenderGroup[TYPE_END];
	CScene*									m_pScene;
	LPDIRECT3DDEVICE9						m_pGraphicDev;
private:
	explicit	CRenderer(void);
private:
	void Render_Priority(void);
	void Render_NoneAlpha(void);
	void Render_Alpha(void);
	void Render_UI(void);
	void Clear_RenderGroup(void);
public:
	HRESULT Initialize_Renderer(void);
	void	Render(void);
public:
	void SetCurrentScene(CScene* pScene);
	void Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pGameObject);
public:
	static CRenderer* Create(void);
public:
	~CRenderer(void);
};