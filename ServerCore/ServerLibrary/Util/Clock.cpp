#include "stdafx.h"
#include "Clock.h"

Clock::Clock()
{
	serverStartTick_ = this->systemTick();
}

Clock::~Clock()
{

}

tick_t Clock::serverStartTick()
{
	return serverStartTick_;
}

tick_t Clock::systemTick()
{
	return system_clock::to_time_t(system_clock::now());
}

tick_t Clock::strToTick(wstr_t str, WCHAR *fmt /*= DB_TIME_FORMAT*/)
{
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;

	swscanf_s(str.c_str(), fmt, &year, &month, &day, &hour, &minute, &second);

	//			초,		분,		시,	일,		월(0부터시작),	년(1900년부터시작)
	tm time = { second, minute, hour, day, month - 1, year - 1900 };

	return mktime(&time);
}

wstr_t Clock::tickToStr(tick_t tick, WCHAR *fmt /*= DATETIME_FORMAT*/)
{
	array<WCHAR, SIZE_128> timeStr;

	tm time;
	localtime_s(&time, &tick);
	wcsftime(timeStr.data(), timeStr.size(), fmt, &time);	

	return timeStr.data();
}

wstr_t Clock::nowTime(WCHAR *fmt /*= DATETIME_FORMAT*/)
{
	return this->tickToStr(this->systemTick(), fmt);
}

wstr_t Clock::nowTimeWithMilliSec(WCHAR *fmt /*= DATETIME_FORMAT*/)
{
#if 0	//주석의 한 종류로 코드 비교 테스트 시에 0과 1로 바꿔가면서 테스트를 할수 있음.
	timePoint now = system_clock::now();
	timePoint oldSecond = system_clock::from_time_t(this->systemTick());

	duration<double> milliseconds = now - oldSecond;
	array<WCHAR, SIZE_8> milliStr;
	snwprintf(milliStr, L"%03d", (int)(milliSecond.count() * 1000));
#else
	high_resolution_clock::time_point point = high_resolution_clock::now();
	milliseconds ms = duration_cast<milliseconds>(point.time_since_epoch());

	seconds s = duration_cast<seconds>(ms);
	tick_t t = s.count();
	std::size_t fractionalSeconds = ms.count() % 1000;
	array<WCHAR, SIZE_8> milliStr;
	snwprintf(milliStr, L"%03d", (int)(fractionalSeconds));
#endif
	wstr_t timeString = this->tickToStr(this->systemTick(), fmt);
	timeString += L".";
	timeString += milliStr.data();
	return timeString;
}

wstr_t Clock::today()
{
	return this->tickToStr(this->systemTick(), DATE_FORMAT);
}

wstr_t Clock::tomorrow()
{
	return this->tickToStr(this->systemTick() + DAY_TO_TICK(1), DATE_FORMAT);
}

wstr_t Clock::yesterday()
{
	return this->tickToStr(this->systemTick() - DAY_TO_TICK(1), DATE_FORMAT);
}

DayOfTheWeek Clock::todayOfTheWeek()
{
	tm time;
	tick_t tick = this->systemTick();
	localtime_s(&time, &tick);
	return (DayOfTheWeek)time.tm_wday;
}