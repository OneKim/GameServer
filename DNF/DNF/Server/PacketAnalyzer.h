#pragma once
#include "stdafx.h"

class PacketAnalyzer
{
public:
	Packet* analyzer(const char *rowPacket, size_t size);
};

static PacketAnalyzer packetAnalyzer;