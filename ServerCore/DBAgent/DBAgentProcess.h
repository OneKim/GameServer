#pragma once
#include "stdafx.h"

class DBAgentProcess : public ContentsProcess
{
public:
	DBAgentProcess();
private:
	void		registSubPacketFunc();
	static void	IPacket_ID_PW(Session *session, Packet *rowPacket);
};