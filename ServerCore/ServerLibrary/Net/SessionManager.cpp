#include "stdafx.h"
#include "SessionManager.h"
#include "IOCPServer.h"

SessionManager::SessionManager(int maxConnection /*= SESSION_CAPACITY*/)
: lock_(L"SessionManager")
{
	sessionSeed_ = 1;
	maxConnection_ = maxConnection;
	this->commandFuncInitialize();
}

SessionManager::~SessionManager()
{
	vector<Session *> removeSessionVec;
	removeSessionVec.resize(sessionList_.size());
	std::copy(sessionList_.begin(), sessionList_.end(), removeSessionVec.begin());
	for (auto session : removeSessionVec) {
		session->onClose();
	}
	sessionList_.clear();
}

list<Session*>& SessionManager::sessionList()
{
	return sessionList_;
}

oid_t SessionManager::createSessionId()
{
	return sessionSeed_++;
}

bool SessionManager::addSession(Session *session)
{
	SAFE_LOCK(lock_);
	auto findSession = std::find(sessionList_.begin(), sessionList_.end(), session);
	if (findSession != sessionList_.end()) {
		return false;
	}
	if (sessionCount_ > maxConnection_) {
		SLog(L"* session so busy. count[%d]", sessionCount_);
		return false;
	}

	session->setId(this->createSessionId());
	sessionList_.push_back(session);
	++sessionCount_;
	return true;
}

//소켓을 닫으라는 클라이언트에게 보냅니다.
bool SessionManager::closeSession(Session *session)
{
	SAFE_LOCK(lock_);
	if (session == nullptr) {
		return false;
	}
	auto findSession = std::find(sessionList_.begin(), sessionList_.end(), session);
	if (findSession != sessionList_.end()) {
		Session *delSession = *findSession;
		SLog(L"* detected close by client [%s]", delSession->clientAddress().c_str());
		::closesocket(delSession->socket());

		sessionList_.remove(delSession);
		--sessionCount_;
		SAFE_DELETE(delSession);
		return true;
	}
	return false;
}

//소켓을 강제로 닫습니다.
void SessionManager::forceCloseSession(Session *session)
{
	SAFE_LOCK(lock_);
	if (!session) {
		return;
	}

	//우아한 종료 유도. 원래는 클라이언트에서 서버 접속을 종료하도록 유도해야 한다.
	LINGER linger;
	linger.l_onoff = 1;		//사용
	linger.l_linger = 0;	//대기시간, 0일시 완료 안된 패킷 버리고 즉시 종료.

	::setsockopt(session->socket(), SOL_SOCKET, SO_LINGER, (char* )&linger, sizeof(linger));
	this->closeSession(session);
}

Session* SessionManager::session(oid_t id)
{
	SAFE_LOCK(lock_);
	Session *findSession = nullptr;

	for (auto session : sessionList_) {
		if (session->id() == id) {
			findSession = session;
			break;
		}
	}

	return findSession;
}

void SessionManager::runCommand(wstr_t cmdLine)
{
	std::size_t	found = cmdLine.find(L' ');
	wstr_t command;
	wstr_t arg;
	if (found != wstr_t::npos) {
		command = cmdLine.substr(0, found);
		arg = cmdLine.substr(found);
	}
	else {
		command = cmdLine;
	}

	auto cmdFunc = serverCommand_.at(command);
	if (cmdFunc) {
		cmdFunc(&sessionList_, &arg);
	}
}

void SessionManager::commandFuncInitialize()
{
#if 0
	//기본적인 3개만 생성, 이후 늘어나면 별도 클래스로 분리
	auto notifyFunc = [](SessionList *sessionList, wstr_t *arg) {
		auto eachFunc = [arg](void *atom) {
			Session *session = (Session*)atom;
			if (session->type() == SESSION_TYPE_TERMINAL) {
				return;
			}
			array<CHAR, SIZE_256> tmpBuf;
			StrConvW2A((WCHAR*)arg->c_str(), tmpBuf.data(), tmpBuf.size());

			PK_S_ANS_CHATTING retPacket;
			retPacket.name_ = "Server";
			retPacket.text_ = "* Notify : ";
			retPacket.text_ += tmpBuf.data();

			session->sendPacket(&retPacket);
		};

		for (auto session : *sessionList) {
			eachFunc(session);
		}
	};

	auto kickoffFunc = [](SessionList *sessionList, wstr_t *arg) {
		vector<Session *> removeSessionVec;
		auto eachFunc = [&removeSessionVec, arg](void *atom) {
			Session *session = (Session*)atom;
			if (session->type() == SESSION_TYPE_TERMINAL) {
				return;
			}

			PK_S_ANS_CHATTING retPacket;
			retPacket.name_ = "Server";
			retPacket.text_ = "! Kick off by Server";
			session->sendPacket(&retPacket);

			removeSessionVec.push_back(session);
		};
		for (auto session : *sessionList) {
			eachFunc(session);
		}

		for (auto session : removeSessionVec) {
			session->onClose();
		}
	};

	auto exitFunc = [](SessionList *sessionList, wstr_t *arg) {
		_shutdown = true;
	};

	//명력어 등록
	serverCommand_.insert(make_pair(L"/notify", notifyFunc));
	serverCommand_.insert(make_pair(L"/kickoff", kickoffFunc));
	serverCommand_.insert(make_pair(L"/exit", exitFunc));
#endif
}