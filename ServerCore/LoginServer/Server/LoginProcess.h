#pragma once
#include "stdafx.h"

class LoginProcess : public ContentsProcess
{
public:
	LoginProcess();
private:
	void		registSubPacketFunc();
	static void	Packet_ID_PW(Session *session, Packet *rowPacket);
	static void	IDB_Packet_ID_PW(Session *session, Packet *rowPacket);
	static void	Packet_Chatting(Session *session, Packet *rowPacket);
};
