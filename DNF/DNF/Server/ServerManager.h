#pragma once

#include "stdafx.h"

#define MAX_IOCP_THREAD		(1)

class ServerManager
{
	DECLARE_SINGLETON(ServerManager)
public:
	enum SOCKET_TYPE { SOCKET_LOGINCHATTING, SOCKET_GAMECONTENTS, SOCKET_END };
private:
	WSADATA		m_Wsa;
	array<SOCKET, SOCKET_END>	m_Socket;
	HANDLE		m_IOCP;
	HANDLE		m_ReceiveThread;
	array<HANDLE, MAX_IOCP_THREAD>	m_WorkerThread;
	string		m_ID;
	string		m_PASSWORD;
	array<bool, SOCKET_END>		m_CheckSocket;
private:
	explicit	ServerManager(void);
	static UINT WINAPI Receive_Thread(LPVOID pServerManager);
	static UINT WINAPI Worker_Thread(LPVOID pServerManager);
public:
	HRESULT		Initialize_ServerManager(void);
	void		Update(const _float& fTimeDelta);
	bool		Connect_Server(char* pIp, int iPort, SOCKET_TYPE eType);
	bool		Close_Socket(SOCKET_TYPE eType);
	bool		Send_Packet(Packet* pPacket, SOCKET_TYPE eType);
	HANDLE		Get_IOCP(void) { return m_IOCP; }
	SOCKET		Get_Socket(SOCKET_TYPE eType) { return m_Socket[eType]; }
	bool		Get_CheckSocket(SOCKET_TYPE eType) { return m_CheckSocket[eType]; }
public:
	~ServerManager(void);
};