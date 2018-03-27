#include "AppTime.h"
#include <chrono>

static auto start = std::chrono::high_resolution_clock::now();

App::Time::Time(bool empty)
{
	if (!empty)
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto micro = std::chrono::duration_cast<std::chrono::microseconds>(now - start).count();
		_time = micro;
	}
}


App::Time::Time(const Time &t) : _time(t._time)
{}


App::Time& App::Time::operator= (const Time &t)
{
	_time = t._time;
	return *this;
}


App::Time::~Time() {}


App::Time App::Time::Milli(unsigned long long int t)
{
	Time time(true);
	time._time = t * 1000;
	return time;
}


App::Time App::Time::Micro(unsigned long long int t)
{
	Time time(true);
	time._time = t;
	return time;
}


App::Time App::Time::Seconds(unsigned long long int t)
{
	Time time(true);
	time._time = t * 1000000;
	return time;
}


App::Time App::Time::operator+ (const Time &t) const
{
	Time time(true);
	time._time = _time + t._time;
	return time;
}


App::Time App::Time::operator- (const Time &t) const
{
	Time time(true);
	time._time = _time - t._time;
	return time;
}


void App::Time::operator+= (const Time &t)
{
	_time += t._time;
}


void App::Time::operator-= (const Time &t)
{
	_time -= t._time;
}


bool App::Time::operator< (const Time &t) const
{
	return _time < t._time;
}


bool App::Time::operator> (const Time &t) const
{
	return _time > t._time;
}


bool App::Time::operator<= (const Time &t) const
{
	return _time <= t._time;
}


bool App::Time::operator>= (const Time &t) const
{
	return _time >= t._time;
}


bool App::Time::operator== (const Time &t) const
{
	return _time == t._time;
}


bool App::Time::operator!= (const Time &t) const
{
	return _time != t._time;
}


unsigned long long App::Time::toSeconds() const
{
	return _time / 1000000;
}


float App::Time::toRoundedSeconds() const
{
	return ((float)(_time)) / 1000000.0f;
}


unsigned long long App::Time::toMilliseconds() const
{
	return _time / 1000;
}


float App::Time::toRoundedMilliseconds() const
{
	return ((float)(_time)) / 1000.0f;
}


unsigned long long App::Time::toMicroseconds() const
{
	return _time;
}


float App::Time::toRoundedMicroseconds() const
{
	return (float)(_time);
}
