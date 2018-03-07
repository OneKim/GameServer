#pragma once

#include "stdafx.h"

class CWinSocket
{
	WSADATA		m_Wsa;
	SOCKET		m_Socket;

public:
	CWinSocket()
	{
		static bool init = false;
		if (init) {
			return;
		}

		if (WSAStartup(MAKEWORD(2, 2), &m_Wsa) != 0 ) {
			MSG_BOX(L"WSA Startup Fail");
			exit(0);
		}

		/*m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		SOCKADDR_IN	serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(9000);
		inet_pton(AF_INET, "127.0.1.1", &(serverAddr.sin_addr));

		bind(m_Socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

		serverAddr.sin_port = htons(9000);
		inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr));
		if (-1 == connect(m_Socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr))) {
			int a = 0;
		}	

		PK_C_REQ_ID_PW* packet = (PK_C_REQ_ID_PW*)packetFactory.getPacket(E_C_REQ_ID_PW);
		packet->id_ = "anjelgo";
		packet->password_ = "anjelgo";

		Stream stream;
		packet->encode(stream);

		packet_size_t offset = 0;
		array<char, SOCKET_BUF_SIZE> buffer;
		const size_t packetHeaderSize = sizeof(packet_size_t);

		packet_size_t packetLen[1] = { (packet_size_t)packetHeaderSize + (packet_size_t)stream.size(), };

		memcpy_s(buffer.data() + offset, buffer.max_size(), (void*)packetLen, packetHeaderSize);
		offset += packetHeaderSize;

		packetObfuscation.encodingHeader((Byte*)buffer.data(), packetHeaderSize);
		packetObfuscation.encodingData((Byte*)stream.data(), stream.size());

		memcpy_s(buffer.data() + offset, buffer.max_size(), stream.data(), packetLen[0]);
		offset += stream.size();

		send(m_Socket, buffer.data(), offset, 0);*/

		init = true;
	}
	~CWinSocket()
	{
		closesocket(m_Socket);
		WSACleanup();
	}
};

static CWinSocket Socket;