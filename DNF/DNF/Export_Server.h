#pragma once

#include "./Server/Stream.h"
#include "./Server/PacketHeader.h"
#include "./Server/PacketClass.h"
#include "./Server/PacketFactory.h"
#include "./Server/PacketObfuscation.h"
#include "./Server/PacketAnalyzer.h"
#include "./Server/ServerManager.h"

namespace Engine
{
	/////////////////////////////////////////////////////////////
	//For.ServerManager

	// For.Getter

	// For.Setter

	// For.General
	inline HRESULT	Initialize_ServerManager(void);

	/////////////////////////////////////////////////////////////
	//For.Release
	inline void Release_Server(void);

#include "Export_Server.inl"

}