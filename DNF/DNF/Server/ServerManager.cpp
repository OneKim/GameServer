#include "stdafx.h"
#include "ServerManager.h"
#include "PacketClass.h"

IMPLEMENT_SINGLETON(ServerManager)

ServerManager::ServerManager(void)
	: m_ContentsProcess(NULL)
	, m_ID("anjelgo1")
	, m_PASSWORD("anjelgo1")
	, m_CHARACTER(L"")
{

}

UINT WINAPI ServerManager::Receive_Thread(LPVOID lpParam)
{
	SOCKET sock = (SOCKET)lpParam;

	array<char, SOCKET_BUF_SIZE> buf;
	int iReadLen = 0;
	int iRecvLen = 0;
	int iTotalBytes = 0;
	int iPacketHeaderSize = sizeof(packet_size_t);
	bool bRecvCheck = false;

	while (true) {

		buf.fill(0);
		iReadLen = 0;
		bRecvCheck = false;

		while (true) {
			iRecvLen = recv(sock, &buf[iReadLen], SOCKET_BUF_SIZE - 1, 0);
			if (iRecvLen != SOCKET_ERROR) {

				iReadLen += iRecvLen;

				if ((false == bRecvCheck) && (iReadLen >= iPacketHeaderSize)) {
					packet_size_t packetLen[1] = { 0, };
					memcpy_s((void *)packetLen, sizeof(packetLen), (void *)&buf, iPacketHeaderSize);
					packetObfuscation.decodingHeader((Byte*)&packetLen, iPacketHeaderSize);
					iTotalBytes = packetLen[0];
					bRecvCheck = true;
				}

				if (iReadLen >= iTotalBytes) {
					packet_size_t packetDataSize = packet_size_t(iTotalBytes - iPacketHeaderSize);
					Byte *packetData = (Byte*)&buf + iPacketHeaderSize;
					packetObfuscation.decodingData(packetData, packetDataSize);
					Engine::Push_Packet(packetAnalyzer.analyzer((const char *)packetData, packetDataSize));
					break;
				}
			}
		}
	}	

	return 0;
}

HRESULT ServerManager::Initialize_ServerManager(void)
{
	if (WSAStartup(MAKEWORD(2, 2), &m_Wsa) != 0) {
		MSG_BOX(L"WSA Startup Fail");
		return E_FAIL;
	}

	//컨텐츠 프로세스 생성
	m_ContentsProcess = shared_ptr<ContentsProcess>(ContentsProcess::Create());

	//로그인 서버 연결
	if (false == this->Connect_Server(g_LoginServerName, g_LoginServerPort, SOCKET_LOGINCHATTING))
		return E_FAIL;	

	//Thread 생성
	for (int i = 0; i < SOCKET_END; ++i) {
		m_ReceiveThread[i] = (HANDLE)_beginthreadex(NULL, 0, Receive_Thread, (void*)m_Socket[i], 0, NULL);
	}		

	//로그인 패킷 전송
	PK_C_REQ_ID_PW packet;
	packet.id_ = m_ID;
	packet.password_ = m_PASSWORD;
	if (false == this->Send_Packet(&packet, SOCKET_LOGINCHATTING))
		return E_FAIL;

	return S_OK;
}

void ServerManager::Update(const _float& fTimeDelta)
{
	m_ContentsProcess->Update(fTimeDelta);
}

bool ServerManager::Connect_Server(const char* pIp, _int iPort, SOCKET_TYPE eType)
{
	SOCKADDR_IN	serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(iPort);
	inet_pton(AF_INET, pIp, &(serverAddr.sin_addr));

	m_Socket[eType] = WSASocket(AF_INET, SOCK_STREAM, NULL, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (SOCKET_ERROR == connect(m_Socket[eType], (SOCKADDR*)&serverAddr, sizeof(serverAddr)))
		return false;

	return true;
}

void ServerManager::DisConnect_Server(SOCKET_TYPE eType)
{
	closesocket(m_Socket[eType]);
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

void ServerManager::Push_Packet(Packet * pPacket)
{
	if (NULL == pPacket)
		return;

	m_ContentsProcess->Push_Packet(pPacket);
}

ServerManager::~ServerManager(void)
{	
	PK_C_REQ_EXIT exitPacket;
	for (int i = 0; i < SOCKET_END; ++i)
		this->Send_Packet(&exitPacket, (SOCKET_TYPE)i);

	for (auto handle : m_ReceiveThread)
		CloseHandle(handle);

	for (auto sock : m_Socket)
		closesocket(sock);

	WSACleanup();
}
