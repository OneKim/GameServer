
/////////////////////////////////////////////////////////////
//For.ServerManager

// For.Getter

// For.Setter

// For.General
HRESULT	Initialize_ServerManager(void)
{
	return ServerManager::Get_Instance()->Initialize_ServerManager();
}


/////////////////////////////////////////////////////////////
//For.Release
void Release_Server(void)
{
	ServerManager::Get_Instance().~shared_ptr();
}