
/////////////////////////////////////////////////////////////
//For.ServerManager

// For.Getter
wstring Get_ID(void)
{
	return ServerManager::Get_Instance()->Get_ID();
}

// For.Setter
void Push_Packet(Packet* pPacket)
{
	ServerManager::Get_Instance()->Push_Packet(pPacket);
}

bool Connect_Server(const char* pIp, _int iPort, SOCKET_TYPE eType)
{
	return ServerManager::Get_Instance()->Connect_Server(pIp, iPort, eType);
}

void DisConnect_Server(SOCKET_TYPE eType)
{
	ServerManager::Get_Instance()->DisConnect_Server(eType);
}

// For.General
HRESULT	Initialize_ServerManager(void)
{
	return ServerManager::Get_Instance()->Initialize_ServerManager();
}

void Update_ServerManager(const _float & fTimeDelta)
{
	ServerManager::Get_Instance()->Update(fTimeDelta);
}

bool Send_Packet(Packet* pPacket, SOCKET_TYPE eType)
{
	return ServerManager::Get_Instance()->Send_Packet(pPacket, eType);
}

/////////////////////////////////////////////////////////////
//For.ChattingManager

// For.Getter

// For.Setter
void Set_MsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	ChattingManager::Get_Instance()->Set_MsgProc(message, wParam, lParam);
}

// For.General
HRESULT	Initialize_ChattingManager(void)
{
	return ChattingManager::Get_Instance()->Initialize_ChattingManager();
}

void Update_ChattingManager(const _float& fTimeDelta)
{
	ChattingManager::Get_Instance()->Update(fTimeDelta);
}

void Render_ChattingManager(void)
{
	ChattingManager::Get_Instance()->Render();
}

/////////////////////////////////////////////////////////////
//For.Release
void Release_Server(void)
{	
	ServerManager::Get_Instance().~shared_ptr();
}