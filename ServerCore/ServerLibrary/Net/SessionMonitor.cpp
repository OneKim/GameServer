#include "stdafx.h"
#include "SessionMonitor.h"

SessionMonitor::SessionMonitor()
{
	static bool init = false;
	if (init) {
		return;
	}
	init = true;

	const int MONITOR_REPORTING_SEC = 1;
	TaskManager::getInstance().add(this, MONITOR_REPORTING_SEC, TICK_INFINTY);
}

void SessionMonitor::tick()
{
	//10초간 방응 없으면 끊기
#ifdef _DEBUG
	const int MAX_HEART_BEAT = 10000; //디버깅을 위해 1000초
#else
	const int MAX_HEART_BEAT = 10;
#endif // _DEBUG
	auto list = SessionManager::getInstance().sessionList();
	tick_t now = CLOCK.systemTick();

	for (auto session : list) {
		if (session->type() != SESSION_TYPE_CLIENT) {
			continue;
		}

		tick_t lastTick = session->heartBeat();
		if (now - lastTick > MAX_HEART_BEAT) {
			SLog(L"* [%s] Closing by heartBeat", session->clientAddress().c_str());
			session->onClose(true);
		}
	}
}