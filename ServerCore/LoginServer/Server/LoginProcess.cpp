#include "stdafx.h"
#include "LoginProcess.h"

LoginProcess::LoginProcess()
{
	this->registSubPacketFunc();
}

void LoginProcess::registSubPacketFunc()
{
	runFuncTable_.insert(make_pair(E_C_REQ_ID_PW, &LoginProcess::Packet_ID_PW));
	runFuncTable_.insert(make_pair(E_I_DB_ANS_ID_PW, &LoginProcess::IDB_Packet_ID_PW));
	runFuncTable_.insert(make_pair(E_C_REQ_CHATTING, &LoginProcess::Packet_Chatting));
}

//------------------------------------------------------------------------//
//패킷 처리 정의
void LoginProcess::Packet_ID_PW(Session *session, Packet *rowPacket)
{
	PK_C_REQ_ID_PW *packet = (PK_C_REQ_ID_PW *)rowPacket;
	SLog(L"* id/pw packet: %S / %S", packet->id_, packet->password_.c_str());

	PK_I_DB_REQ_ID_PW dbPacket;
	dbPacket.clientId_ = (UInt64)session->id();
	dbPacket.id_ = packet->id_;
	dbPacket.password_ = packet->password_;

	Terminal *terminal = TerminalManager::getInstance().terminal(L"DBAgent");
	terminal->sendPacket(&dbPacket);
}

void LoginProcess::IDB_Packet_ID_PW(Session *session, Packet *rowPacket)
{
	PK_I_DB_ANS_ID_PW *packet = (PK_I_DB_ANS_ID_PW *)rowPacket;
	SLog(L"* id/ pw result = %d", packet->result_);

	Session *clientSession = SessionManager::getInstance().session(packet->clientId_);
	if (clientSession == nullptr) {
		return;
	}

	const int authFail = 0;
	if (packet->result_ == authFail) {
		PK_S_ANS_ID_PW_FAIL ansPacket;
		clientSession->sendPacket(&ansPacket);
		return;
	}
	else {
		PK_S_ANS_ID_PW_SUCCESS ansPacket;
		clientSession->sendPacket(&ansPacket);
		return;
	}
}

void LoginProcess::Packet_Chatting(Session *session, Packet *rowPacket)
{
	PK_C_REQ_CHATTING *packet = (PK_C_REQ_CHATTING *)rowPacket;
	SLog(L"* chatting packet: %S", packet->text_.c_str());

	PK_S_ANS_CHATTING retPacket;
	retPacket.name_ = "test ";			//XXX 임시 코드, 패킷 테스트로 넣었음
	retPacket.text_ = "re : ";
	retPacket.text_ += packet->text_;
	SLog(L"* send message %S, %S", retPacket.name_.c_str(), retPacket.text_.c_str());
	session->sendPacket(&retPacket);
}
