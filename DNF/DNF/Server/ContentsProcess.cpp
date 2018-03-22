#include "stdafx.h"
#include "ContentsProcess.h"

ContentsProcess::ContentsProcess(void)
{

}

HRESULT ContentsProcess::Initialize_ContentsProcess(void)
{
	m_PacketQueue = shared_ptr<ThreadJobQueue<Packet*>>(new ThreadJobQueue<Packet*>);
	NULL_CHECK_RETURN(m_PacketQueue, E_FAIL);

	this->Regist_PacketFunc();

	return S_OK;
}

void ContentsProcess::Regist_PacketFunc(void)
{
#define INSERT_PACKET_PROCESS(type)			m_mapRunFunc.insert(make_pair(E_##type, &ContentsProcess::##type))

	INSERT_PACKET_PROCESS(S_ANS_ID_PW_SUCCESS);
	INSERT_PACKET_PROCESS(S_ANS_EXIT);
}

void ContentsProcess::Update(const _float & fTimeDelta)
{
	Packet *packet = NULL;
	RunFunc runFunction = NULL;
	while (m_PacketQueue->pop(packet)) {
		auto itr = m_mapRunFunc.find(packet->type());
		if (itr != m_mapRunFunc.end()) {
			runFunction = itr->second;
			runFunction(packet);
		}		
		Safe_Delete(packet);
	}
}

void ContentsProcess::Push_Packet(Packet* pPacket)
{
	m_PacketQueue->push(pPacket);
}

ContentsProcess * ContentsProcess::Create(void)
{
	ContentsProcess* pInstance = new ContentsProcess;
	if (FAILED(pInstance->Initialize_ContentsProcess())) {
		MSG_BOX(L"ContentsProcess Created Failed");
		Safe_Delete(pInstance);
	}
	return pInstance;
}

ContentsProcess::~ContentsProcess(void)
{
	Packet *packet = NULL;
	while (m_PacketQueue->pop(packet)) {
		Safe_Delete(packet);
	}

	m_mapRunFunc.clear();
}

//------------------------------------------------------------------------//
void ContentsProcess::S_ANS_EXIT(Packet * pPacket)
{
	int a = 0;	
}

void ContentsProcess::S_ANS_ID_PW_SUCCESS(Packet * pPacket)
{
	PK_S_ANS_ID_PW_SUCCESS* packet = (PK_S_ANS_ID_PW_SUCCESS*)pPacket;
	
	PK_C_REQ_EXIT exitPacket;
	Engine::Send_Packet(&exitPacket, SOCKET_LOGINCHATTING);

	Engine::DisConnect_Server(SOCKET_LOGINCHATTING);

	Engine::Connect_Server(g_ChattingServerName, g_ChattingServerPort, SOCKET_LOGINCHATTING);

	PK_C_REQ_REGIST_CHATTING_NAME registPacket;
	registPacket.name_ = packet->name_;
	Engine::Send_Packet(&registPacket, SOCKET_LOGINCHATTING);
}