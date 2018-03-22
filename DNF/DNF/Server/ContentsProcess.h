#pragma once

class ContentsProcess
{
	typedef void(*RunFunc)(Packet* pPacket);
private:	
	map<PacketType, RunFunc>				m_mapRunFunc;
	shared_ptr<ThreadJobQueue<Packet*>>		m_PacketQueue;
private:
	explicit ContentsProcess(void);
	HRESULT Initialize_ContentsProcess(void);
	void	Regist_PacketFunc(void);
public:
	void	Update(const _float& fTimeDelta);
	void	Push_Packet(Packet* pPacket);
public:
	static ContentsProcess* Create(void);
	~ContentsProcess(void);
public:
	static void S_ANS_EXIT(Packet* pPacket);
	static void S_ANS_ID_PW_SUCCESS(Packet* pPacket);	
};