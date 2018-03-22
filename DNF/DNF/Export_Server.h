#pragma once

#include "./Server/Stream.h"
#include "./Server/PacketHeader.h"
#include "./Server/PacketClass.h"
#include "./Server/PacketFactory.h"
#include "./Server/PacketObfuscation.h"
#include "./Server/PacketAnalyzer.h"
#include "./Server/ThreadJobQueue.h"
#include "./Server/ContentsProcess.h"
#include "./Server/ServerManager.h"
#include "./Server/ChattingManager.h"

namespace Engine
{
	/////////////////////////////////////////////////////////////
	//For.ServerManager

	// For.Getter

	// For.Setter
	inline void		Push_Packet(Packet* pPacket);
	inline bool		Connect_Server(const char* pIp, _int iPort, SOCKET_TYPE eType);
	inline void		DisConnect_Server(SOCKET_TYPE eType);

	// For.General
	inline HRESULT	Initialize_ServerManager(void);
	inline void		Update_ServerManager(const _float& fTimeDelta);
	inline bool		Send_Packet(Packet* pPacket, SOCKET_TYPE eType);

	/////////////////////////////////////////////////////////////
	//For.ChattingManager

	// For.Getter

	// For.Setter

	// For.General
	inline HRESULT	Initialize_ChattingManager(void);
	inline void		Update_ChattingManager(const _float& fTimeDelta);
	inline void		Render_ChattingManager(void);

	/////////////////////////////////////////////////////////////
	//For.Release
	inline void Release_Server(void);

#include "Export_Server.inl"

}