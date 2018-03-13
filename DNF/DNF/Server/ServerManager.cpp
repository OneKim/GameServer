#include "stdafx.h"
#include "ServerManager.h"
#include "PacketClass.h"

char*	pLoginServer = "127.0.0.1";
int		iLoginPort = 9000;

struct SOCKET_DATA
{
	SOCKET			socket_;
	SOCKADDR_IN		addrInfo_;
};

struct IO_DATA
{
	OVERLAPPED		overlapped_;
	WSABUF			wsaBuf_;

	int				totalBytes_;
	int				currentBytes_;
	char			buffer_[SOCKET_BUF_SIZE];
};


IMPLEMENT_SINGLETON(ServerManager)

ServerManager::ServerManager(void)
	: m_ID("anjelgo")
	, m_PASSWORD("anjelgo")
{

}

UINT WINAPI ServerManager::Receive_Thread(LPVOID pServerManager)
{
	ServerManager* serverManager = (ServerManager*)pServerManager;	

	while (true) {
		
		for (int i = 0; i < SOCKET_END; ++i)
		{
			if (false == serverManager->Get_CheckSocket((SOCKET_TYPE)i))
				continue;
			DWORD flags = 0;
			DWORD recvBytes;

			shared_ptr<IO_DATA> ioData(new IO_DATA);
			ZeroMemory(ioData.get(), sizeof(IO_DATA));
			ioData->totalBytes_ = sizeof(ioData->buffer_);
			ioData->currentBytes_ = 0;
			ioData->wsaBuf_.buf = ioData->buffer_;
			ioData->wsaBuf_.len = ioData->totalBytes_;

			WSARecv(serverManager->Get_Socket((SOCKET_TYPE)i), &ioData->wsaBuf_, 1, &recvBytes, &flags, &(ioData->overlapped_), NULL);
		}			
	}

	return 0;
}

UINT WINAPI ServerManager::Worker_Thread(LPVOID pServerManager)
{
	ServerManager* serverManager = (ServerManager*)pServerManager;

	while (true) {
		SOCKET_DATA*	socketData = NULL;
		IO_DATA*		ioData = NULL;
		DWORD			trafficSize;

		BOOL success = GetQueuedCompletionStatus(serverManager->Get_IOCP(), &trafficSize, (PULONG_PTR)&socketData, (LPOVERLAPPED*)&ioData, INFINITE);

		if (FALSE == success)
			continue;

		packet_size_t offset = 0;
		packet_size_t packetLen[1] = { 0, };
		packet_size_t totalBytes;
		const size_t packetHeaderSize = sizeof(packet_size_t);
		memcpy_s((void *)packetLen, sizeof(packetLen), (void *)ioData->buffer_, sizeof(packetLen));
		packetObfuscation.decodingHeader((Byte*)&packetLen, sizeof(packetLen));
		totalBytes = (size_t)packetLen[0];
		offset += sizeof(packetLen);

		packet_size_t packetDataSize = packet_size_t(totalBytes - packetHeaderSize);
		Byte *packetData = (Byte*)ioData->buffer_ + offset;

		packetObfuscation.decodingData(packetData, packetDataSize);
		Packet *packet = packetAnalyzer.analyzer((const char *)packetData, packetDataSize);
	}

	return 0;
}

HRESULT ServerManager::Initialize_ServerManager(void)
{
	if (WSAStartup(MAKEWORD(2, 2), &m_Wsa) != 0) {
		MSG_BOX(L"WSA Startup Fail");
		return E_FAIL;
	}

	for (int i = 0; i < SOCKET_END; ++i) {
		m_Socket[i] = WSASocket(AF_INET, SOCK_STREAM, NULL, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (SOCKET_ERROR == m_Socket[i])
			return E_FAIL;
	}

	//IOCP 생성
	m_IOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, MAX_IOCP_THREAD);
	NULL_CHECK_RETURN(m_IOCP, E_FAIL);

	//로그인 서버 연결
	if (false == this->Connect_Server(pLoginServer, iLoginPort, ServerManager::SOCKET_LOGINCHATTING))
		return E_FAIL;	

	//Thread 생성
	m_ReceiveThread = (HANDLE)_beginthreadex(NULL, 0, Receive_Thread, (void*)this, 0, NULL);
	/*for (int i = 0; i < MAX_IOCP_THREAD; ++i)
		m_WorkerThread[i] = (HANDLE)_beginthreadex(NULL, 0, Worker_Thread, (void*)this, 0, NULL);*/

	shared_ptr<PK_C_REQ_ID_PW> packet = shared_ptr<PK_C_REQ_ID_PW>((PK_C_REQ_ID_PW*)packetFactory.getPacket(E_C_REQ_ID_PW));
	packet->id_ = m_ID;
	packet->password_ = m_PASSWORD;
	if (false == this->Send_Packet(packet.get(), ServerManager::SOCKET_LOGINCHATTING))
		return E_FAIL;

	return S_OK;
}

void ServerManager::Update(const _float& fTimeDelta)
{

}

bool ServerManager::Connect_Server(char* pIp, int iPort, SOCKET_TYPE eType)
{
	SOCKADDR_IN	serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(iPort);
	inet_pton(AF_INET, pIp, &(serverAddr.sin_addr));	

	if (SOCKET_ERROR == connect(m_Socket[eType], (SOCKADDR*)&serverAddr, sizeof(serverAddr)))
		return false;

	shared_ptr<SOCKET_DATA> socketData(new SOCKET_DATA);
	ZeroMemory(socketData.get(), sizeof(SOCKET_DATA));
	socketData->socket_ = m_Socket[eType];
	memcpy_s((void*)&socketData->addrInfo_, sizeof(SOCKADDR_IN), (void*)&serverAddr, sizeof(SOCKADDR_IN));

	if (NULL == CreateIoCompletionPort((HANDLE)m_Socket[eType], m_IOCP, ULONG_PTR(socketData.get()), 0))
		return false;

	m_CheckSocket[eType] = true;

	return true;
}

bool ServerManager::Close_Socket(SOCKET_TYPE eType)
{
	m_CheckSocket[eType] = false;
	if (SOCKET_ERROR == closesocket(m_Socket[eType]))
		return false;	
	return true;
}

bool ServerManager::Send_Packet(Packet* pPacket, SOCKET_TYPE eType)
{
	NULL_CHECK_RETURN(pPacket, false);

	Stream stream;
	pPacket->encode(stream);
	packet_size_t offset = 0;
	array<char, SOCKET_BUF_SIZE> buffer;
	const size_t packetHeaderSize = sizeof(packet_size_t);

	packet_size_t packetLen[1] = { (packet_size_t)packetHeaderSize + (packet_size_t)stream.size(), };
	memcpy_s(buffer.data(), buffer.max_size(), (void*)packetLen, packetHeaderSize);
	offset += packetHeaderSize;

	packetObfuscation.encodingHeader((Byte*)buffer.data(), packetHeaderSize);
	packetObfuscation.encodingData((Byte*)stream.data(), stream.size());

	memcpy_s(buffer.data() + offset, buffer.max_size() - offset, stream.data(), stream.size());
	offset += (packet_size_t)stream.size();

	if (SOCKET_ERROR == send(m_Socket[eType], buffer.data(), offset, 0))
		return false;

	return true;
}

ServerManager::~ServerManager(void)
{
	for (auto handle : m_WorkerThread)
		CloseHandle(handle);
	CloseHandle(m_ReceiveThread);

	for (auto sock : m_Socket)
		closesocket(sock);

	CloseHandle(m_IOCP);

	WSACleanup();
}
