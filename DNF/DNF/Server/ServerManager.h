#pragma once

#include "stdafx.h"

class ServerManager
{
	DECLARE_SINGLETON(ServerManager)
private:
	WSADATA		m_Wsa;
	array<SOCKET, SOCKET_END>	m_Socket;
	array<HANDLE, SOCKET_END>	m_ReceiveThread;
	shared_ptr<ContentsProcess>	m_ContentsProcess;
	string		m_ID;
	string		m_PASSWORD;
	wstring		m_CHARACTER;
private:
	explicit	ServerManager(void);
	static UINT WINAPI Receive_Thread(LPVOID lpParam);
public:
	HRESULT		Initialize_ServerManager(void);
	void		Update(const _float& fTimeDelta);
	bool		Connect_Server(const char* pIp, _int iPort, SOCKET_TYPE eType);
	void		DisConnect_Server(SOCKET_TYPE eType);
	bool		Send_Packet(Packet* pPacket, SOCKET_TYPE eType);
	void		Push_Packet(Packet* pPacket);
	SOCKET		Get_Socket(SOCKET_TYPE eType) { return m_Socket[eType]; }
	wstring		Get_CHARACTER(void) { return m_CHARACTER;	}
	void		Set_CHARACTER(wstring wsCharactor) { m_CHARACTER = wsCharactor;	}
public:
	~ServerManager(void);
};